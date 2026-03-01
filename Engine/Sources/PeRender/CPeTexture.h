#ifndef PEENGINE_CPE_TEXTURE_H
#define PEENGINE_CPE_TEXTURE_H

#include "CPeGraphicalVertex.h"
#include "CPeBluePrints.h"
#include <vector>
#include <optional>
#include <string>

namespace vk {
    class CPeTexture : public TextureObject {
    public:
        std::string texturePath;
        bool loaded = false;

        CPeTexture* createTextureObject(vk::GenericRenderer& renderer, std::string texturePath);

        CPeTexture(vk::GenericRenderer& renderer,  std::string texturePath);

        void Load();
        VkDescriptorSet& GetTextureDescriptorSet();
        void Free();
        void Destroy();
    private:

        uint32_t mipLevels;
        VkImage textureImage;
        VkDeviceMemory textureImageMemory;
        VkImageView textureImageView;
        VkSampler textureSampler;
        VkDescriptorSet descriptorSet;

        VkDevice& device;
        VkPhysicalDevice& physicalDevice;
        VkQueue& graphicsQueue;
        VkCommandPool& commandPool;
        VkDescriptorPool& descriptorPool;
        VkDescriptorSetLayout& uniformDescriptorSetLayout;
        VkDescriptorSetLayout& textureDescriptorSetLayout;

        bool posHasChanged = false;

        void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
        VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);
        void createImage(
            uint32_t width,
            uint32_t height,
            uint32_t mipLevels,
            VkSampleCountFlagBits numSamples,
            VkFormat format,
            VkImageTiling tiling,
            VkImageUsageFlags usage,
            VkMemoryPropertyFlags properties,
            VkImage& image,
            VkDeviceMemory& imageMemory
        );
        void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);
        void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

        void createTextureImage(const char* path);
        void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);
        void createTextureImageView();
        void createTextureSampler();
        void createTextureDescriptorSet();

        VkCommandBuffer beginSingleTimeCommands();
        void endSingleTimeCommands(VkCommandBuffer commandBuffer);
    };
}

#endif