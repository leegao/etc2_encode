#include <cstdint>
#include <iterator>
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

#include <vulkan/vulkan.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <ktx.h>

struct ETC2Block {
    uint32_t eacHigh;
    uint32_t eacLow;
    uint32_t etcColorPayload;
    uint32_t etcPixelPayload;
};

struct Clock {
    uint64_t start;
    float mse;
    uint32_t unused;
    uint8_t reconstructed[64];
};

struct PushConstants {
    int32_t width;
    int32_t height;
    uint32_t flag;
};

#define VK_CHECK(x) do { \
    VkResult err = x; \
    if (err) { \
        std::cerr << "Vulkan Error detected: " #x << " = " << err << " (" << __LINE__ << ")" << std::endl; \
        std::exit(1); \
    } \
} while(0)

// const uint32_t COMPUTE_SPIRV[] = { 
//     #include "compress_.inc"
// };

#include "compress.h"
#define COMPUTE_SPIRV ((const uint32_t*) compress_spv)
#define COMPUTE_SPIRV_SIZE (compress_spv_len)

uint32_t FindMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties) {
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);
    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }
    return 0;
}

#define GL_RGBA                           0x1908
#define GL_COMPRESSED_RGBA8_ETC2_EAC      0x9278

bool WriteETC2ToKTX(const std::string& filename, 
                    uint32_t width, 
                    uint32_t height, 
                    const std::vector<ETC2Block>& etc2Data) 
{
    ktxTextureCreateInfo createInfo;
    createInfo.glInternalformat = GL_COMPRESSED_RGBA8_ETC2_EAC;
    createInfo.vkFormat = VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK;
    createInfo.baseWidth = width;
    createInfo.baseHeight = height;
    createInfo.baseDepth = 1;
    createInfo.numDimensions = 2;
    createInfo.numLevels = 1;
    createInfo.numLayers = 1;
    createInfo.numFaces = 1;
    createInfo.isArray = KTX_FALSE;
    createInfo.generateMipmaps = KTX_FALSE;

    ktxTexture1* texture = nullptr;
    KTX_error_code result = ktxTexture1_Create(&createInfo, KTX_TEXTURE_CREATE_ALLOC_STORAGE, &texture);
    
    if (result != KTX_SUCCESS) {
        std::cerr << "ktxTexture1_Create failed. Error code: " << result << std::endl;
        return false;
    }

    result = ktxTexture_SetImageFromMemory(ktxTexture(texture), 0, 0, 0, (const unsigned char*) etc2Data.data(), etc2Data.size() * sizeof(ETC2Block));
    if (result != KTX_SUCCESS) {
        std::cerr << "ktxTexture_SetImageFromMemory failed. Error code: " << result << std::endl;
        return false;
    }

    result = ktxTexture_WriteToNamedFile(ktxTexture(texture), filename.c_str());
    if (result != KTX_SUCCESS) {
        std::cerr << "ktxTexture_WriteToNamedFile failed. Error code: " << result << std::endl;
        return false;
    }

    ktxTexture_Destroy(ktxTexture(texture));
    std::cout << "Successfully wrote etc2 to " << filename << std::endl;
    return true;
}

int main() {
    int width, height, channels;
    stbi_uc* pixelData = stbi_load("test.png", &width, &height, &channels, STBI_rgb_alpha);
    if (!pixelData) {
        std::cerr << "test.png does not exist" << std::endl;
        return -1;
    }
    
    int blocksX = (width + 3) / 4;
    int blocksY = (height + 3) / 4;
    size_t totalBlocks = static_cast<size_t>(blocksX) * blocksY;
    size_t compressedBufferSize = totalBlocks * sizeof(ETC2Block);
    size_t profileBufferSize = totalBlocks * sizeof(Clock); // for diagnostics

    VkInstance instance;
    VkApplicationInfo appInfo{ VK_STRUCTURE_TYPE_APPLICATION_INFO, nullptr, "", 1, "Engine", 1, VK_API_VERSION_1_1 };
    VkInstanceCreateInfo instInfo{ VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, nullptr, 0, &appInfo, 0, nullptr, 0, nullptr };
    VK_CHECK(vkCreateInstance(&instInfo, nullptr, &instance));

    uint32_t gpuCount = 1;
    VK_CHECK(vkEnumeratePhysicalDevices(instance, &gpuCount, nullptr));
    if (gpuCount == 0) {
        std::cerr << "No Vulkan GPU found!" << std::endl;
        std::exit(1);
    }
    
    if (gpuCount > 0) {
        std::cout << "Found " << gpuCount << " gpus, using the first one." << std::endl;
    }
    
    std::vector<VkPhysicalDevice> physicalDevices(gpuCount);
    VK_CHECK(vkEnumeratePhysicalDevices(instance, &gpuCount, physicalDevices.data()));
    VkPhysicalDevice physicalDevice = physicalDevices[0];

    uint32_t queueFamilyIndex = 0;
    uint32_t queueCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueCount, nullptr);
    std::vector<VkQueueFamilyProperties> queueProps(queueCount);
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueCount, queueProps.data());
    for (uint32_t i = 0; i < queueCount; ++i) {
        if ((queueProps[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) && (queueProps[i].queueFlags & VK_QUEUE_COMPUTE_BIT)) {
            std::cout << "Queue family index " << i << " supports both G&C." << std::endl;
            queueFamilyIndex = i;
            break;
        }
    }

    float queuePriority = 1.0f;
    VkDeviceQueueCreateInfo queueInfo{ VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO, nullptr, 0, queueFamilyIndex, 1, &queuePriority };
    VkDeviceCreateInfo deviceInfo{ VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO, nullptr, 0, 1, &queueInfo, 0, nullptr, 0, nullptr, nullptr };
    VkDevice device;
    VK_CHECK(vkCreateDevice(physicalDevice, &deviceInfo, nullptr, &device));

    VkQueue universalQueue;
    vkGetDeviceQueue(device, queueFamilyIndex, 0, &universalQueue);

    VkCommandPool commandPool;
    VkCommandPoolCreateInfo poolInfo{ VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO, nullptr, VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT, queueFamilyIndex };
    VK_CHECK(vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool));

    VkBuffer stagingBuffer;
    size_t stagingBufferSize = static_cast<size_t>(width) * height * 4;
    VkBufferCreateInfo stageBufInfo{ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO, nullptr, 0, stagingBufferSize, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_SRC_BIT };
    VK_CHECK(vkCreateBuffer(device, &stageBufInfo, nullptr, &stagingBuffer));
    VkMemoryRequirements stageReqs;
    vkGetBufferMemoryRequirements(device, stagingBuffer, &stageReqs);
    VkMemoryAllocateInfo stageAlloc{ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO, nullptr, stageReqs.size, FindMemoryType(physicalDevice, stageReqs.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) };
    VkDeviceMemory stagingMemory;
    VK_CHECK(vkAllocateMemory(device, &stageAlloc, nullptr, &stagingMemory));
    vkBindBufferMemory(device, stagingBuffer, stagingMemory, 0);

    // Load test.png into staging buffer
    void* mappedData;
    vkMapMemory(device, stagingMemory, 0, stagingBufferSize, 0, &mappedData);
    std::memcpy(mappedData, pixelData, stagingBufferSize);
    vkUnmapMemory(device, stagingMemory);
    stbi_image_free(pixelData);

    VkBuffer compressedBuffer;
    VkBufferCreateInfo compBufInfo{ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO, nullptr, 0, compressedBufferSize, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT };
    VK_CHECK(vkCreateBuffer(device, &compBufInfo, nullptr, &compressedBuffer));
    VkMemoryRequirements compReqs;
    vkGetBufferMemoryRequirements(device, compressedBuffer, &compReqs);
    VkMemoryAllocateInfo compAlloc{ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO, nullptr, compReqs.size, FindMemoryType(physicalDevice, compReqs.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) };
    VkDeviceMemory compressedMemory;
    VK_CHECK(vkAllocateMemory(device, &compAlloc, nullptr, &compressedMemory));
    vkBindBufferMemory(device, compressedBuffer, compressedMemory, 0);

    VkBuffer profileBuffer;
    VkBufferCreateInfo profileBufferInfo{ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO, nullptr, 0, profileBufferSize, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT };
    VK_CHECK(vkCreateBuffer(device, &profileBufferInfo, nullptr, &profileBuffer));
    VkMemoryRequirements profileBufferReqs;
    vkGetBufferMemoryRequirements(device, profileBuffer, &profileBufferReqs);
    VkMemoryAllocateInfo profileBufferAlloc{ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO, nullptr, profileBufferReqs.size, FindMemoryType(physicalDevice, profileBufferReqs.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) };
    VkDeviceMemory profileBufferMemory;
    VK_CHECK(vkAllocateMemory(device, &profileBufferAlloc, nullptr, &profileBufferMemory));
    VK_CHECK(vkBindBufferMemory(device, profileBuffer, profileBufferMemory, 0));

    VkCommandBuffer cmd;
    VkCommandBufferAllocateInfo cmdAllocInfo{ VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO, nullptr, commandPool, VK_COMMAND_BUFFER_LEVEL_PRIMARY, 1 };
    vkAllocateCommandBuffers(device, &cmdAllocInfo, &cmd);
    VkCommandBufferBeginInfo beginInfo{ VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO, nullptr, VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT };
    vkBeginCommandBuffer(cmd, &beginInfo);

    VkDescriptorSetLayoutBinding bindings[3] = {};
    // Binding 0: source buffer (uint8_t4 pixels)
    bindings[0].binding = 0;
    bindings[0].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
    bindings[0].descriptorCount = 1;
    bindings[0].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
    // Binding 1: etc2 ssbo
    bindings[1].binding = 1;
    bindings[1].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
    bindings[1].descriptorCount = 1;
    bindings[1].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
    // Binding 2: profile ssbo (clock, diagnostics)
    bindings[2].binding = 2;
    bindings[2].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
    bindings[2].descriptorCount = 1;
    bindings[2].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;

    VkDescriptorSetLayoutCreateInfo layoutInfo{ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO, nullptr, 0, 3, bindings };
    VkDescriptorSetLayout descriptorSetLayout;
    VK_CHECK(vkCreateDescriptorSetLayout(device, &layoutInfo, nullptr, &descriptorSetLayout));

    VkPushConstantRange pushRange{};
    pushRange.stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
    pushRange.offset = 0;
    pushRange.size = sizeof(PushConstants);

    VkPipelineLayoutCreateInfo pipeLayoutInfo{ VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO, nullptr, 0, 1, &descriptorSetLayout, 1, &pushRange };
    VkPipelineLayout pipelineLayout;
    VK_CHECK(vkCreatePipelineLayout(device, &pipeLayoutInfo, nullptr, &pipelineLayout));

    // Load compress.spv into a compute pipeline
    VkShaderModuleCreateInfo shaderInfo{ VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO, nullptr, 0, COMPUTE_SPIRV_SIZE, COMPUTE_SPIRV };
    VkShaderModule computeShaderModule;
    VK_CHECK(vkCreateShaderModule(device, &shaderInfo, nullptr, &computeShaderModule));

    VkPipelineShaderStageCreateInfo stageInfo{ VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO, nullptr, 0, VK_SHADER_STAGE_COMPUTE_BIT, computeShaderModule, "main", nullptr };

    VkComputePipelineCreateInfo computePipeInfo{ VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO, nullptr, 0, stageInfo, pipelineLayout, VK_NULL_HANDLE, 0 };
    VkPipeline computePipeline;
    VK_CHECK(vkCreateComputePipelines(device, VK_NULL_HANDLE, 1, &computePipeInfo, nullptr, &computePipeline));

    VkDescriptorPoolSize poolSizes[3] = {};
    poolSizes[0].type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER; // src buffer
    poolSizes[0].descriptorCount = 1;
    poolSizes[1].type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER; // etc2 ssbo
    poolSizes[1].descriptorCount = 1;
    poolSizes[2].type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER; // profile ssbo
    poolSizes[2].descriptorCount = 1;

    VkDescriptorPoolCreateInfo descPoolInfo{ VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO, nullptr, 0, 1, 3, poolSizes };
    VkDescriptorPool descriptorPool;
    VK_CHECK(vkCreateDescriptorPool(device, &descPoolInfo, nullptr, &descriptorPool));
    VkDescriptorSetAllocateInfo allocInfo{ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO, nullptr, descriptorPool, 1, &descriptorSetLayout };
    VkDescriptorSet descriptorSet;
    VK_CHECK(vkAllocateDescriptorSets(device, &allocInfo, &descriptorSet));

    VkDescriptorBufferInfo srcBufferDescInfo{};
    srcBufferDescInfo.buffer = stagingBuffer;
    srcBufferDescInfo.offset = 0;
    srcBufferDescInfo.range = stagingBufferSize;

    VkDescriptorBufferInfo bufferDescInfo{};
    bufferDescInfo.buffer = compressedBuffer;
    bufferDescInfo.offset = 0;
    bufferDescInfo.range = compressedBufferSize;

    VkDescriptorBufferInfo bufferDescInfo2{};
    bufferDescInfo2.buffer = profileBuffer;
    bufferDescInfo2.offset = 0;
    bufferDescInfo2.range = profileBufferSize;

    VkWriteDescriptorSet descriptorWrites[3] = {};
    descriptorWrites[0] = { VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET, nullptr, descriptorSet, 0, 0, 1, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, nullptr, &srcBufferDescInfo, nullptr };
    descriptorWrites[1] = { VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET, nullptr, descriptorSet, 1, 0, 1, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, nullptr, &bufferDescInfo, nullptr };
    descriptorWrites[2] = { VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET, nullptr, descriptorSet, 2, 0, 1, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, nullptr, &bufferDescInfo2, nullptr };

    vkUpdateDescriptorSets(device, 3, descriptorWrites, 0, nullptr);

    // Dispatch the encoder
    vkCmdBindPipeline(cmd, VK_PIPELINE_BIND_POINT_COMPUTE, computePipeline);
    vkCmdBindDescriptorSets(cmd, VK_PIPELINE_BIND_POINT_COMPUTE, pipelineLayout, 0, 1, &descriptorSet, 0, nullptr);

    PushConstants constants{ 
        width, 
        height,
        0, // FLAG - 0: normal, 1: NO ETC2, 2: NO 2-Means 
    };
    vkCmdPushConstants(cmd, pipelineLayout, VK_SHADER_STAGE_COMPUTE_BIT, 0, sizeof(PushConstants), &constants);

    uint32_t groupCountX = (blocksX + 7) / 8;
    uint32_t groupCountY = (blocksY + 7) / 8;
    vkCmdDispatch(cmd, groupCountX, groupCountY, 1);

    // Barrier to ensure compute writes are visible to CPU
    VkBufferMemoryBarrier compFinishBarrier{ VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER, nullptr, VK_ACCESS_SHADER_WRITE_BIT, VK_ACCESS_HOST_READ_BIT, queueFamilyIndex, queueFamilyIndex, compressedBuffer, 0, compressedBufferSize };
    vkCmdPipelineBarrier(cmd, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, VK_PIPELINE_STAGE_HOST_BIT, 0, 0, nullptr, 1, &compFinishBarrier, 0, nullptr);

    vkDestroyShaderModule(device, computeShaderModule, nullptr);
    vkEndCommandBuffer(cmd);

    VkSubmitInfo submitInfo{ VK_STRUCTURE_TYPE_SUBMIT_INFO, nullptr, 0, nullptr, nullptr, 1, &cmd, 0, nullptr };
    vkQueueSubmit(universalQueue, 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(universalQueue);

    std::vector<ETC2Block> encodedBlocks(totalBlocks);
    vkMapMemory(device, compressedMemory, 0, compressedBufferSize, 0, &mappedData);
    std::memcpy(encodedBlocks.data(), mappedData, compressedBufferSize);
    vkUnmapMemory(device, compressedMemory);
    
    std::vector<Clock> profiler(totalBlocks);
    vkMapMemory(device, profileBufferMemory, 0, profileBufferSize, 0, &mappedData);
    std::memcpy(profiler.data(), mappedData, profileBufferSize);
    vkUnmapMemory(device, profileBufferMemory);

    uint64_t first_start = profiler[0].start;
    uint64_t last_start = profiler[0].start;
    double mse = 0.0;
    for (Clock clock : profiler) {
        if (clock.start < first_start) first_start = clock.start;
        if (clock.start > last_start) last_start = clock.start;
        mse += double(clock.mse);
    }
    std::cout << "Total time: " << (double)(last_start - first_start) / 100000.0 << " ms" << std::endl;
    std::cout << "  MSE: " << mse / profiler.size() << ", PSNR: " << -10 * log10(mse / profiler.size()) << std::endl;

    // profiler.reconstructed contains a 4x4 block of reconstructed rgba8 pixels, going left to right and top to down
    // write this to reconstructed.png
    std::vector<uint8_t> reconstructedImage(width * height * 4);

    for (int by = 0; by < blocksY; ++by) {
        for (int bx = 0; bx < blocksX; ++bx) {
            size_t blockIdx = by * blocksX + bx;
            const uint8_t* blockData = profiler[blockIdx].reconstructed;

            // Loop over 4x4 pixels in the current block
            for (int y = 0; y < 4; ++y) {
                for (int x = 0; x < 4; ++x) {
                    int pixelX = bx * 4 + x;
                    int pixelY = by * 4 + y;

                    // Bounds check: Only write if inside original image dimensions
                    if (pixelX < width && pixelY < height) {
                        int srcIdx = (y * 4 + x) * 4; // 4 bytes per pixel (RGBA)
                        int dstIdx = (pixelY * width + pixelX) * 4;

                        reconstructedImage[dstIdx + 0] = blockData[srcIdx + 0]; // R
                        reconstructedImage[dstIdx + 1] = blockData[srcIdx + 1]; // G
                        reconstructedImage[dstIdx + 2] = blockData[srcIdx + 2]; // B
                        reconstructedImage[dstIdx + 3] = blockData[srcIdx + 3]; // A
                    }
                }
            }
        }
    }

    if (stbi_write_png("reconstructed.png", width, height, 4, reconstructedImage.data(), width * 4)) {
        std::cout << "Successfully wrote reconstructed.png" << std::endl;
    } else {
        std::cerr << "Failed to write reconstructed.png" << std::endl;
    }

    std::ofstream outFile("output.etc2", std::ios::binary);
    if (outFile.is_open()) {
        outFile.write(reinterpret_cast<const char*>(encodedBlocks.data()), compressedBufferSize);
        outFile.close();
        std::cout << "Wrote the raw etc2 ssbo to output.etc2" << std::endl;
    }

    WriteETC2ToKTX("output.ktx", width, height, encodedBlocks);
    return 0;
}
