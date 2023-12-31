#ifndef PEENGINE_CPE_BLUE_PRINTS_H
#define PEENGINE_CPE_BLUE_PRINTS_H

#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <string>

namespace vk {
    class ModelObject {        
    public:
        bool loaded;

        virtual void Load() = 0;
        virtual void Destroy() = 0;
        virtual void Render(VkCommandBuffer commandBuffer, VkPipelineLayout& pipelineLayout) = 0;
    };

    class TextureObject {
    public:
        std::string texturePath;
        bool loaded;

        //TextureObject(GenericRenderer& renderer, std::string texturePath);

        virtual void Load() = 0;
        virtual VkDescriptorSet& GetTextureDescriptorSet() = 0;
        virtual void Free() = 0;
        virtual void Destroy() = 0;
    };

    class GenericRenderer {
    public:
        virtual void setViewMatrix(glm::mat4&) = 0;
        virtual VkDevice& getDevice() = 0;
        virtual VkPhysicalDevice& getPhysicalDevice() = 0;
        virtual VkCommandPool& getCommandPool() = 0;
        virtual VkQueue& getGraphicsQueue() = 0;
        virtual VkDescriptorPool& getDescriptorPool() = 0;
        virtual VkDescriptorSetLayout& getUniformDescriptorSetlayout() = 0;
        virtual VkDescriptorSetLayout& getTextureDescriptorSetlayout() = 0;

        virtual void AddModel(ModelObject& object) = 0;
        virtual TextureObject& AddTexture(std::string texture) = 0;

        virtual void RemoveModel(ModelObject& object) = 0;
    };

    class GenericViewManager {
    public:
        virtual void rotateAroundX(float angle) = 0;
        virtual void rotateAroundY(float angle) = 0;
        virtual void rotateAroundZ(float angle) = 0;
        virtual void rotateAroundAxis(float angle, float x, float y, float z) = 0;
        virtual void rotateUpDown(float angle) = 0;

        virtual void goForwardX(float distance) = 0;
        virtual void goForwardY(float distance) = 0;
        virtual void goForwardZ(float distance) = 0;

        virtual void goForward(float fistance) = 0;
        virtual void goRight(float fistance) = 0;
        virtual void goUp(float fistance) = 0;

        virtual void submitViewMatrix() = 0;

        virtual void changeCameraOrientation(float centerX, float centerY, float centerZ) = 0;
        virtual void changeCameraPosition(float eyeX, float eyeY, float eyeZ) = 0;
    }; 
}

#endif