#include <cstdint>
#include <iterator>
#include <sys/types.h>
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
#include <string>
#include <ktx.h>

#define GL_RGBA8                                     0x8058
#define GL_RGBA16F                                   0x881A
#define GL_COMPRESSED_RGB_S3TC_DXT1_EXT              0x83F0
#define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT             0x83F1
#define GL_COMPRESSED_SRGB_S3TC_DXT1_EXT             0x8C4C
#define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT       0x8C4D
#define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT             0x83F2
#define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT       0x8C4E
#define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT             0x83F3
#define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT       0x8C4F
#define GL_COMPRESSED_RED_RGTC1                      0x8DBB
#define GL_COMPRESSED_SIGNED_RED_RGTC1               0x8DBC
#define GL_COMPRESSED_RG_RGTC2                       0x8DBD
#define GL_COMPRESSED_SIGNED_RG_RGTC2                0x8DBE
#define GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT        0x8E8F
#define GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT          0x8E8E
#define GL_COMPRESSED_RGBA_BPTC_UNORM                0x8E8C
#define GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM          0x8E8D
#define GL_COMPRESSED_RGBA_ASTC_4x4_KHR              0x93B0
#define GL_COMPRESSED_RGBA8_ETC2_EAC                 0x9278
#define GL_COMPRESSED_RGB8_ETC2                      0x9274

uint32_t VkFormatToGLInternalFormat(VkFormat vkFormat) {
    switch (vkFormat) {
        case VK_FORMAT_R8G8B8A8_UNORM:             return GL_RGBA8;
        case VK_FORMAT_R16G16B16A16_SFLOAT:        return GL_RGBA16F;
        case VK_FORMAT_BC1_RGB_UNORM_BLOCK:        return GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
        case VK_FORMAT_BC1_RGB_SRGB_BLOCK:         return GL_COMPRESSED_SRGB_S3TC_DXT1_EXT;
        case VK_FORMAT_BC1_RGBA_UNORM_BLOCK:       return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
        case VK_FORMAT_BC1_RGBA_SRGB_BLOCK:        return GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT;
        case VK_FORMAT_BC2_UNORM_BLOCK:            return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
        case VK_FORMAT_BC2_SRGB_BLOCK:             return GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT;
        case VK_FORMAT_BC3_UNORM_BLOCK:            return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
        case VK_FORMAT_BC3_SRGB_BLOCK:             return GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT;
        case VK_FORMAT_BC4_UNORM_BLOCK:            return GL_COMPRESSED_RED_RGTC1;
        case VK_FORMAT_BC4_SNORM_BLOCK:            return GL_COMPRESSED_SIGNED_RED_RGTC1;
        case VK_FORMAT_BC5_UNORM_BLOCK:            return GL_COMPRESSED_RG_RGTC2;
        case VK_FORMAT_BC5_SNORM_BLOCK:            return GL_COMPRESSED_SIGNED_RG_RGTC2;
        case VK_FORMAT_BC6H_UFLOAT_BLOCK:          return GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT;
        case VK_FORMAT_BC6H_SFLOAT_BLOCK:          return GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT;
        case VK_FORMAT_BC7_UNORM_BLOCK:            return GL_COMPRESSED_RGBA_BPTC_UNORM;
        case VK_FORMAT_BC7_SRGB_BLOCK:             return GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM;
        case VK_FORMAT_ASTC_4x4_UNORM_BLOCK:       return GL_COMPRESSED_RGBA_ASTC_4x4_KHR;

        default:
            return GL_RGBA8;
    }
}

bool WriteToKTX(const std::string& filename,
    VkFormat format, uint32_t width, uint32_t height, const std::vector<uint8_t>& data, ssize_t size)
{
    ktxTextureCreateInfo createInfo;
    createInfo.glInternalformat = VkFormatToGLInternalFormat(format);
    createInfo.vkFormat = format;
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
        std::cerr << "ktxTexture1_Create failed. Error code: " << result << ", fmt: " << format << std::endl;
        return false;
    }

    result = ktxTexture_SetImageFromMemory(ktxTexture(texture), 0, 0, 0, (const unsigned char*) data.data(), size);
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
    std::cout << "Successfully wrote to " << filename << std::endl;
    return true;
}


std::vector<uint8_t> LoadRawData(const std::string& filename, int* width, int* height, VkFormat* format) {
    // Parse filename: ${ID}_fmt_${VK_FORMAT_INT}_${W}x${H}.bin
    std::string::size_type sep = filename.find_last_of("/\\");
    std::string basename = (sep == std::string::npos) ? filename : filename.substr(sep + 1);

    if (basename.size() > 4 && basename.substr(basename.size() - 4) == ".bin") {
        basename = basename.substr(0, basename.size() - 4);
    }
    std::string::size_type fmtPos = basename.find("_fmt_");
    if (fmtPos == std::string::npos) {
        throw std::runtime_error("Invalid filename format, expected '_fmt_' in: " + filename);
    }
    std::string::size_type xPos = basename.find('x', fmtPos + 5);
    if (xPos == std::string::npos) {
        throw std::runtime_error("Invalid filename format, expected 'WxH' in: " + filename);
    }
    std::string::size_type dimUnderscore = basename.rfind('_', xPos);
    if (dimUnderscore == std::string::npos || dimUnderscore <= fmtPos + 5) {
        throw std::runtime_error("Invalid filename format, expected '_WxH' in: " + filename);
    }
    std::string formatStr = basename.substr(fmtPos + 5, dimUnderscore - (fmtPos + 5));
    int formatInt = std::stoi(formatStr);
    *format = static_cast<VkFormat>(formatInt);
    std::string widthStr = basename.substr(dimUnderscore + 1, xPos - (dimUnderscore + 1));
    std::string heightStr = basename.substr(xPos + 1);
    *width = std::stoi(widthStr);
    *height = std::stoi(heightStr);
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open raw file: " + filename);
    }
    size_t fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<uint8_t> data(fileSize);
    file.read(reinterpret_cast<char*>(data.data()), fileSize);

    return data;
}

int main() {
    int width, height;
    VkFormat format;

    auto pixelData = LoadRawData("6816_fmt_37_512x512.bin", &width, &height, &format);
    if (pixelData.empty()) {
        std::cerr << "Failed to load data" << std::endl;
        return -1;
    }

    std::cout << "Loaded: " << width << "x" << height
              << " format=" << format
              << " size=" << pixelData.size() << " bytes" << std::endl;

    WriteToKTX("6816_fmt_37_512x512.ktx", format, width, height, pixelData, pixelData.size());
    return 0;
}
