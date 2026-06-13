#include <cstdint>
#include <iterator>
#include <vulkan/vulkan_core.h>
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

struct ASTCBlock {
    uint32_t x;
    uint32_t y;
    uint32_t z;
    uint32_t w;
};

struct ASTCParameters {
    uint8_t ep0[4];
    uint8_t ep1[4];
    uint8_t weights[16];
    uint astc_seed;
    uint partition_map;
};

struct Clock {
    uint64_t start;
    float mse;
    uint32_t unused;
    uint8_t reconstructed[64];
    ASTCParameters params;
};

struct PushConstants {
    int32_t width;
    int32_t height;
    uint32_t flag;
};

struct LUT {
    uint32_t lut2[1024]; // 1024-entry (4KB)
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

#include "astc_enc.h"
#define COMPUTE_SPIRV ((const uint32_t*) astc_enc_spv)
#define COMPUTE_SPIRV_SIZE (astc_enc_spv_len)

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
#define GL_COMPRESSED_RGB8_ETC2           0x9274
#define GL_COMPRESSED_RGBA_ASTC_4x4       0x93B0

bool WriteASTCToKTX(const std::string& filename,
                    uint32_t width,
                    uint32_t height,
                    const std::vector<ASTCBlock>& etc2Data)
{
    ktxTextureCreateInfo createInfo;
    createInfo.glInternalformat = GL_COMPRESSED_RGBA_ASTC_4x4;
    createInfo.vkFormat = VK_FORMAT_ASTC_4x4_UNORM_BLOCK;
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

    int blocksX = (width + 3) / 4;
    int blocksY = (height + 3) / 4;
    size_t totalBlocks = static_cast<size_t>(blocksX) * blocksY;
    int block_size = 16;
    result = ktxTexture_SetImageFromMemory(ktxTexture(texture), 0, 0, 0, (const unsigned char*) etc2Data.data(), totalBlocks * block_size);
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


std::vector<uint8_t> LoadRawRgba8(const std::string& filename, int width, int height) {
    size_t expectedSize = width * height * 4; // 16 bytes per BC6H block

    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open raw rgba8 file: " + filename);
    }

    size_t fileSize = file.tellg();
    if (fileSize != expectedSize) {
        throw std::runtime_error("File size mismatch. Expected: " +
                               std::to_string(expectedSize) + ", Got: " +
                               std::to_string(fileSize));
    }

    file.seekg(0, std::ios::beg);
    std::vector<uint8_t> data(fileSize);
    file.read(reinterpret_cast<char*>(data.data()), fileSize);

    return data;
}

std::vector<uint8_t> LoadRawSfloat16(const std::string& filename, int width, int height) {
    size_t expectedSize = width * height * 4 * 2;

    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open raw sfloat16 file: " + filename);
    }

    size_t fileSize = file.tellg();
    if (fileSize != expectedSize) {
        throw std::runtime_error("File size mismatch. Expected: " +
                               std::to_string(expectedSize) + ", Got: " +
                               std::to_string(fileSize));
    }

    file.seekg(0, std::ios::beg);
    std::vector<uint8_t> data(fileSize);
    file.read(reinterpret_cast<char*>(data.data()), fileSize);

    return data;
}


std::vector<uint8_t> LoadRawData(const std::string& filename, int expectedSize) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open raw file: " + filename);
    }

    size_t fileSize = file.tellg();
    if (fileSize != expectedSize) {
        throw std::runtime_error("File size mismatch. Expected: " +
                               std::to_string(expectedSize) + ", Got: " +
                               std::to_string(fileSize));
    }

    file.seekg(0, std::ios::beg);
    std::vector<uint8_t> data(fileSize);
    file.read(reinterpret_cast<char*>(data.data()), fileSize);

    return data;
}

int main() {
    int width, height, channels;

    auto pixelData = stbi_load("./test.png", &width, &height, &channels, STBI_rgb_alpha);
    if (!pixelData) {
        std::cerr << "test.png does not exist" << std::endl;
        return -1;
    }
    size_t stagingBufferSize = static_cast<size_t>(width) * height * 4;
    auto astc_partition_lut = LoadRawData("astc_2p_4x4_lut_s2.bin", 43692);
    size_t partitionLutBufferSize = static_cast<size_t>(43692);

    auto lut2 = LoadRawData("lut2_packed.bin", 4096);
    struct LUT myLutData = {};
    std::memcpy(myLutData.lut2, lut2.data(), 4096);

    // width = 2048; height = 2048;
    // auto pixelDataVec = LoadRawRgba8("machick.rgba8", width, height);
    // auto pixelData = pixelDataVec.data();
    // if (!pixelData) {
    //     std::cerr << "test.png does not exist" << std::endl;
    //     return -1;
    // }

    // width = 128; height = 128;
    // stagingBufferSize = static_cast<size_t>(width) * height * 8;
    // auto pixelDataVec = LoadRawSfloat16("205.sfloat", width, height);
    // auto pixelData = pixelDataVec.data();
    // if (!pixelData) {
    //     std::cerr << "205.sfloat does not exist" << std::endl;
    //     return -1;
    // }

    // if (stbi_write_png("machick.png", width, height, 4, pixelData, width * 4)) {
    //     std::cout << "Successfully wrote machick.png" << std::endl;
    // } else {
    //     std::cerr << "Failed to write machick.png" << std::endl;
    // }

    int blocksX = (width + 3) / 4;
    int blocksY = (height + 3) / 4;
    size_t totalBlocks = static_cast<size_t>(blocksX) * blocksY;
    size_t compressedBufferSize = totalBlocks * sizeof(ASTCBlock);
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

    VkBuffer partitionLutBuffer;
    VkBufferCreateInfo partitionLutBufferInfo{
        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .size = partitionLutBufferSize,
        .usage = VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
    };
    VK_CHECK(vkCreateBuffer(device, &partitionLutBufferInfo, nullptr, &partitionLutBuffer));
    VkMemoryRequirements partitionLutBufferReqs;
    vkGetBufferMemoryRequirements(device, partitionLutBuffer, &partitionLutBufferReqs);
    VkMemoryAllocateInfo partitionLutBufferAlloc = {
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        .allocationSize = partitionLutBufferReqs.size,
        .memoryTypeIndex = FindMemoryType(
            physicalDevice,
            partitionLutBufferReqs.memoryTypeBits,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT),
    };
    VkDeviceMemory partitionLutBufferMemory;
    VK_CHECK(vkAllocateMemory(device, &partitionLutBufferAlloc, nullptr, &partitionLutBufferMemory));
    vkBindBufferMemory(device, partitionLutBuffer, partitionLutBufferMemory, 0);

    void* mappedData;
    vkMapMemory(device, partitionLutBufferMemory, 0, partitionLutBufferReqs.size, 0, &mappedData);
    std::memcpy(mappedData, astc_partition_lut.data(), partitionLutBufferSize);
    vkUnmapMemory(device, partitionLutBufferMemory);


    VkBuffer lutUniformBuffer;
    VkBufferCreateInfo lutBufferInfo{
        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .size = sizeof(LUT),
        .usage = VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
    };
    VK_CHECK(vkCreateBuffer(device, &lutBufferInfo, nullptr, &lutUniformBuffer));
    VkMemoryRequirements lutBufferReqs;
    vkGetBufferMemoryRequirements(device, lutUniformBuffer, &lutBufferReqs);
    VkMemoryAllocateInfo lutBufferAlloc{
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        .allocationSize = lutBufferReqs.size,
        .memoryTypeIndex = FindMemoryType(
            physicalDevice,
            lutBufferReqs.memoryTypeBits,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
        ),
    };
    VkDeviceMemory lutBufferMemory;
    VK_CHECK(vkAllocateMemory(device, &lutBufferAlloc, nullptr, &lutBufferMemory));
    vkBindBufferMemory(device, lutUniformBuffer, lutBufferMemory, 0);

    void* mappedLutData;
    vkMapMemory(device, lutBufferMemory, 0, lutBufferReqs.size, 0, &mappedLutData);
    std::memcpy(mappedLutData, &myLutData, sizeof(LUT)); // Pass pointer to the struct
    vkUnmapMemory(device, lutBufferMemory);

    VkBuffer stagingBuffer;
    VkBufferCreateInfo stageBufInfo = {
        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .size = stagingBufferSize,
        .usage = VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
    };
    VK_CHECK(vkCreateBuffer(device, &stageBufInfo, nullptr, &stagingBuffer));
    VkMemoryRequirements stageReqs;
    vkGetBufferMemoryRequirements(device, stagingBuffer, &stageReqs);
    VkMemoryAllocateInfo stageAlloc = { VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO, nullptr, stageReqs.size, FindMemoryType(physicalDevice, stageReqs.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) };
    VkDeviceMemory stagingMemory;
    VK_CHECK(vkAllocateMemory(device, &stageAlloc, nullptr, &stagingMemory));
    vkBindBufferMemory(device, stagingBuffer, stagingMemory, 0);

    // Load test.png into staging buffer
    void* mappedPixelData;
    vkMapMemory(device, stagingMemory, 0, stagingBufferSize, 0, &mappedPixelData);
    std::memcpy(mappedPixelData, pixelData, stagingBufferSize);
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
    VkBufferCreateInfo profileBufferInfo{ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO, nullptr, 0, profileBufferSize, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT };
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

    VkDescriptorSetLayoutBinding bindings[5] = {};
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
    // Binding 3: lut uniform buffer
    bindings[3].binding = 3;
    bindings[3].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
    bindings[3].descriptorCount = 1;
    bindings[3].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
    // Binding 4: partitionLutBuffer (astc snapper)
    bindings[4].binding = 4;
    bindings[4].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
    bindings[4].descriptorCount = 1;
    bindings[4].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;

    VkDescriptorSetLayoutCreateInfo layoutInfo{ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO, nullptr, 0, 5, bindings };
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

    VkDescriptorPoolSize poolSizes[1] = {};
    poolSizes[0].type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
    poolSizes[0].descriptorCount = 10;

    VkDescriptorPoolCreateInfo descPoolInfo{ VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO, nullptr, 0, 1, 1, poolSizes };
    VkDescriptorPool descriptorPool;
    VK_CHECK(vkCreateDescriptorPool(device, &descPoolInfo, nullptr, &descriptorPool));
    VkDescriptorSetAllocateInfo allocInfo{ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO, nullptr, descriptorPool, 1, &descriptorSetLayout };
    VkDescriptorSet descriptorSet;
    VK_CHECK(vkAllocateDescriptorSets(device, &allocInfo, &descriptorSet));

    VkDescriptorBufferInfo srcBufferDescInfo{
        .buffer = stagingBuffer,
        .offset = 0,
        .range = stagingBufferSize,
    };

    VkDescriptorBufferInfo bufferDescInfo{
        .buffer = compressedBuffer,
        .offset = 0,
        .range = compressedBufferSize,
    };

    VkDescriptorBufferInfo bufferDescInfo4{
        .buffer = profileBuffer,
        .offset = 0,
        .range = profileBufferSize,
    };

    VkDescriptorBufferInfo bufferDescInfo2{
        .buffer = lutUniformBuffer,
        .offset = 0,
        .range = VK_WHOLE_SIZE,
    };

    VkDescriptorBufferInfo bufferDescInfo3{
        .buffer = partitionLutBuffer,
        .offset = 0,
        .range = VK_WHOLE_SIZE,
    };

    #define DESCRIPTOR_WRITE(_dstBinding, _descriptorType, _pBufferInfo) \
        { \
            .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET, \
            .dstSet = descriptorSet, \
            .dstBinding = _dstBinding, \
            .descriptorCount = 1, \
            .descriptorType = _descriptorType, \
            .pBufferInfo = _pBufferInfo, \
        }
    VkWriteDescriptorSet descriptorWrites[] = {
        DESCRIPTOR_WRITE(0, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, &srcBufferDescInfo),
        DESCRIPTOR_WRITE(1, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, &bufferDescInfo),
        DESCRIPTOR_WRITE(2, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, &bufferDescInfo2),
        DESCRIPTOR_WRITE(3, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, &bufferDescInfo3),
        DESCRIPTOR_WRITE(4, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, &bufferDescInfo4),
    };

    vkUpdateDescriptorSets(device, 5, descriptorWrites, 0, nullptr);

    // Dispatch the encoder
    vkCmdBindPipeline(cmd, VK_PIPELINE_BIND_POINT_COMPUTE, computePipeline);
    vkCmdBindDescriptorSets(cmd, VK_PIPELINE_BIND_POINT_COMPUTE, pipelineLayout, 0, 1, &descriptorSet, 0, nullptr);

    PushConstants constants{
        width,
        height,
        0b00001, // FLAG - 0: normal, 1: AABB, 2: 2-Partition, 4: only 2-Partition, 8 USE sfloat16, 16 USE snorm
    };
    vkCmdPushConstants(cmd, pipelineLayout, VK_SHADER_STAGE_COMPUTE_BIT, 0, sizeof(PushConstants), &constants);

    std::cout << "Encoding ASTC: width=" << width << " height=" << height << " flags=" << constants.flag << std::endl;
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

    std::vector<ASTCBlock> encodedBlocks(totalBlocks);
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
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);
    float timestampPeriod = deviceProperties.limits.timestampPeriod;

    std::cout << "Total time: " << (double)(last_start - first_start) / (1000000.0 / timestampPeriod) << " ms (granularity = " << timestampPeriod << "ns)" << std::endl;
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
                        // std::cout << "Pixel (" << pixelX << ", " << pixelY << "): R=" << (int)reconstructedImage[dstIdx + 0] << " G=" << (int)reconstructedImage[dstIdx + 1] << " B=" << (int)reconstructedImage[dstIdx + 2] << " A=" << (int)reconstructedImage[dstIdx + 3] << std::endl;
                    }
                }
            }
        }
    }

    if (stbi_write_png("reconstructed_astc.png", width, height, 4, reconstructedImage.data(), width * 4)) {
        std::cout << "Successfully wrote reconstructed_astc.png" << std::endl;
    } else {
        std::cerr << "Failed to write reconstructed_astc.png" << std::endl;
    }

    std::ofstream outFile("output.astc", std::ios::binary);
    if (outFile.is_open()) {
        outFile.write(reinterpret_cast<const char*>(encodedBlocks.data()), compressedBufferSize);
        outFile.close();
        std::cout << "Wrote the raw astc ssbo to output.astc" << std::endl;
    }

    WriteASTCToKTX("astc.ktx", width, height, encodedBlocks);

    // WriteASTCToKTX("astc4x42.ktx", 16, 4, {
    //     {0xa7cd0242, 0xc9ad9b4, 0xdbb53dbf, 0x15103b50},
    //     {0x6a150242, 0x1d82fd00, 0x1aa0fe64, 0x86214ac4},
    //     {0xdbb10242, 0x36d4f124, 0xc5a88c08, 0xfff91ffe},
    //     {0xea910242, 0x1d883b8c, 0x46b904b9, 0xea1f26d9},
    // });

    // WriteASTCToKTX("astc4x4.ktx", 4, 4, {encodedBlocks[0]});
    uint idx = 1022;
    std::cout << "block 0: " << std::hex << encodedBlocks[idx].x << ", " << encodedBlocks[idx].y << ", " << encodedBlocks[idx].z << ", " << encodedBlocks[idx].w << std::endl;
    std::cout << "params 0: ep0="
              << std::hex << (int)profiler[idx].params.ep0[0] << " " << (int)profiler[idx].params.ep0[1] << " " << (int)profiler[idx].params.ep0[2] << " " << (int)profiler[idx].params.ep0[3]
              << " ep1=" << (int)profiler[idx].params.ep1[0] << " " << (int)profiler[idx].params.ep1[1] << " " << (int)profiler[idx].params.ep1[2] << " " << (int)profiler[idx].params.ep1[3]
              << " weights=" << std::endl;
    for (int i = 0; i < 16; ++i) {
        std::cout << (int)profiler[idx].params.weights[i] << " ";
    }
    // std::cout << std::endl;
    // std::cout << "astc_seed = " << (int)profiler[0].params.astc_seed << std::endl;
    // for (int i = 0; i < 20; ++i) {
    //     std::cout << "  partition_map[" << i << "] = " << (int)profiler[i].params.partition_map << " vs " << myLutData.lut2[i % 1024] << std::endl;
    // }

    return 0;
}
