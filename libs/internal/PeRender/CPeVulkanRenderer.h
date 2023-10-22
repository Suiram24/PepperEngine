#ifndef PEENGINE_CPEVULKANRENDERER_H
#define PEENGINE_CPEVULKANRENDERER_H

#include "CPeGraphicalVertex.h"
#include "CPeBluePrints.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <optional>
#include <string>

namespace vk {

    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;

    const std::string MODEL_PATH = "models/viking_room.obj";
    const std::string TEXTURE_PATH = "textures/viking_room.png";

    const int MAX_FRAMES_IN_FLIGHT = 2;

    const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

    const std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    class CPeVulkanRenderer: public GenericRenderer {
    public:
        void init();
        void init(GLFWwindow* window);
        void cleanup();
        void beginDrawFrame();
        void endDrawFrame();

        void setViewMatrix(glm::mat4& viewMatrix);
        VkDevice& getDevice();
        VkPhysicalDevice& getPhysicalDevice();
        VkCommandPool& getCommandPool();
        VkQueue& getGraphicsQueue();
        VkDescriptorPool& getDescriptorPool();
        VkDescriptorSetLayout& getUniformDescriptorSetlayout();
        VkDescriptorSetLayout& getTextureDescriptorSetlayout();

        // Models methods
        void AddModel(ModelObject& object);

        void RemoveModel(ModelObject& object);

        void AddTexture(TextureObject& object);

        void SetNearPlan(float distance);

        void SetFarPlan(float distance);

    private:
        glm::mat4* viewMatrix;
        GLFWwindow* window;

        VkInstance instance;
        VkDebugUtilsMessengerEXT debugMessenger;
        VkSurfaceKHR surface;

        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkDevice device;

        VkQueue graphicsQueue;
        VkQueue presentQueue;

        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;
        std::vector<VkImageView> swapChainImageViews;
        std::vector<VkFramebuffer> swapChainFramebuffers;

        VkRenderPass renderPass;
        VkDescriptorSetLayout uniformDescriptorSetLayout;
        VkDescriptorSetLayout textureDescriptorSetLayout;
        VkPipelineLayout pipelineLayout;
        VkPipeline graphicsPipeline;

        VkCommandPool commandPool;

        VkImage depthImage;
        VkDeviceMemory depthImageMemory;
        VkImageView depthImageView;

        VkImage colorImage;
        VkDeviceMemory colorImageMemory;
        VkImageView colorImageView;

        std::vector<VkBuffer> uniformBuffers;
        std::vector<VkDeviceMemory> uniformBuffersMemory;
        std::vector<void*> uniformBuffersMapped;

        VkDescriptorPool descriptorPool;
        std::vector<VkDescriptorSet> descriptorSets;

        std::vector<VkCommandBuffer> commandBuffers;


        VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_1_BIT;

        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;
        uint32_t currentFrame = 0;
        uint32_t imageIndexFrame = 0;

        bool framebufferResized = false;

        float nearPlan = 0.1f;
        float farPlan = 10.0f;

        std::vector<ModelObject*> graphicalObjects;
        std::vector<TextureObject*> textureObjects;

        static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

        void initVulkan();

        void initImGui();

        void cleanupSwapChain();

        void recreateSwapChain();

        void createInstance();

        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

        void setupDebugMessenger();

        void createSurface();

        void pickPhysicalDevice();

        void createLogicalDevice();

        void createSwapChain();

        void createImageViews();

        void createRenderPass();

        void createDescriptorSetLayout();

        void createGraphicsPipeline();

        void createFramebuffers();
        
        void createCommandPool();

        void createDepthResources();

        // Models functions

        void DestroyModels();

        void DestroyTextures();

        void RenderModels(VkCommandBuffer commandBuffer, VkPipelineLayout& pipelineLayout);

        VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

        VkFormat findDepthFormat();

        bool hasStencilComponent(VkFormat format);

        void createTextureImage();

        void createTextureImageView();

        void createTextureSampler();
        
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

        void createColorResources();

        void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);

        void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

        void createUniformBuffers();

        void createDescriptorPool();

        void createDescriptorSets();

        void createBuffer(
            VkDeviceSize size,
            VkBufferUsageFlags usage,
            VkMemoryPropertyFlags properties,
            VkBuffer& buffer,
            VkDeviceMemory& bufferMemory
        );

        VkCommandBuffer beginSingleTimeCommands();

        void endSingleTimeCommands(VkCommandBuffer commandBuffer);

        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

        void createCommandBuffers();

        void beginRecordCommandBuffer(VkCommandBuffer& commandBuffer, uint32_t imageIndex);

        void endRecordCommandBuffer(VkCommandBuffer& commandBuffer);

        void createSyncObjects();

        void setupMatrix();

        void updateUniformBuffer(uint32_t currentImage);

        void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);

        VkSampleCountFlagBits getMaxUsableSampleCount();

        VkShaderModule createShaderModule(const std::vector<char>& code);

        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

        bool isDeviceSuitable(VkPhysicalDevice device);

        bool checkDeviceExtensionSupport(VkPhysicalDevice device);

        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

        std::vector<const char*> getRequiredExtensions();

        bool checkValidationLayerSupport();

        static std::vector<char> readFile(const std::string& filename);

        static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData
        );
    };
    /*
    int main() {
        HelloTriangleApplication app;

        try {
            app.run();
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }
    */
}
#endif