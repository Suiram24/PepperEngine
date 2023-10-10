#ifndef PEENGINE_CPE_BLUE_PRINTS_H
#define PEENGINE_CPE_BLUE_PRINTS_H

#include <vulkan/vulkan.h>

namespace vk {
    class ModelObject {        
    public:
        bool loaded;

        virtual void Load(const char* path) = 0;
        virtual void Load() = 0;
        virtual void Destroy() = 0;
        virtual void Render(VkCommandBuffer commandBuffer) = 0;
    };

    class GenericRenderer {
    public:
        virtual VkDevice& getDevice() = 0;
        virtual VkPhysicalDevice& getPhysicalDevice() = 0;
        virtual VkCommandPool& getCommandPool() = 0;
        virtual VkQueue& getGraphicsQueue() = 0;

        virtual void AddModel(ModelObject& object) = 0;
        virtual void RemoveModel(ModelObject& object) = 0;
    };
}

#endif