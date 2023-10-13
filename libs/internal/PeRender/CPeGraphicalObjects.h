#ifndef PEENGINE_CPE_GRAPHICAL_OBJECT_H
#define PEENGINE_CPE_GRAPHICAL_OBJECT_H

#include "CPeGraphicalVertex.h"
#include "CPeBluePrints.h"
#include <vector>
#include <optional>
#include <string>

namespace vk {
    class ModelWatcher: public ModelObject {
    public:
        glm::vec3 pos;
        glm::vec3 scale;
        

        const char* modelPath;
        bool loaded = false;

        ModelWatcher(vk::GenericRenderer& renderer, std::string modelPath);

        void Load(const char* path);
        void Load();
        void Destroy();
        void Render(VkCommandBuffer commandBuffer, VkPipelineLayout& pipelineLayout);
        void SetPos(float x, float y, float z);
        void SetScale(float s);
    private:
        std::vector<vk::Vertex> vertices;
        std::vector<uint32_t> indices;
        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
        VkBuffer indexBuffer;
        VkDeviceMemory indexBufferMemory;

        VkDevice& device;
        VkPhysicalDevice& physicalDevice;
        VkQueue& graphicsQueue;
        VkCommandPool& commandPool;

        bool posHasChanged = false;
        glm::vec3 translationVector;

        void loadModel(const char* path);
        void createVertexBuffer();
        void createIndexBuffer();
        void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

        VkCommandBuffer beginSingleTimeCommands();
        void endSingleTimeCommands(VkCommandBuffer commandBuffer);
    };
}

#endif