//
// Created by ReSung on 2021-08-14.
//

#ifndef STARENGINE_STARVULKAN_HPP
#define STARENGINE_STARVULKAN_HPP

#include <vulkan/vulkan.h>
#include "../Types/Vertex.hpp"
#include "../Types/UniformBuffer.hpp"

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

class StarVulkan {
private:
    //Structs
    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };
    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };
    struct TextureObject {
        uint32_t mipLevels;
        VkImage textureImage;
        VkDeviceMemory textureImageMemory;
        VkImageView textureImageView;
    };

    //Objects
    VkInstance instance;
    VkSurfaceKHR surface;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_1_BIT;
    VkDevice device;
    VkQueue graphicsQueue, presentQueue;
    VkRenderPass renderPass;

    TextureObject mainTex;

    //region SwapChainObjects
    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    std::vector<VkImageView> swapChainImageViews;
    std::vector<VkFramebuffer> swapChainFrameBuffers;
    //endregion

    //region Command
    VkCommandPool commandPool;
    std::vector<VkCommandBuffer> commandBuffers;
    //endregion

    //region PipelineObjects
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;
    //endregion

    //region VertexObjects
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;
    //endregion

    //region SwapChain
    VkSampler textureSampler;
    //endregion

    //region DescriptorSets
    VkDescriptorPool descriptorPool;
    VkDescriptorSetLayout descriptorSetLayout;
    std::vector<VkDescriptorSet> descriptorSets;
    //endregion

    //Configuration
    const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };
    const std::vector<const char*> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    //Setup
    void InitGLFW();
    void CreateSurface();

    //region PhysicalDevice
    VkPhysicalDevice PickPhysicalDevice();
    bool IsDeviceSuitable(VkPhysicalDevice localDevice);
    StarVulkan::QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
    bool CheckDeviceExtensionSupport(VkPhysicalDevice localDevice);
    StarVulkan::SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice localDevice);
    //endregion

    //region LogicalDevice
    void CreateLogicalDevice();
    //endregion

    //region SwapChain
    void CreateSwapChain();
    void CreateSwapChainImages();
    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    //endregion

    //region Texture
    StarVulkan::TextureObject CreateTexture(char *path, bool generateMipMaps, VkCommandPool commandPool, VkQueue queue);
    void CreateTextureImage(char* path, bool generateMipmaps, uint32_t *mipLevels, VkImage *textureImage, VkDeviceMemory *textureImageMemory, VkCommandPool commandPool, VkQueue queue);
    void CreateImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage *image, VkDeviceMemory *imageMemory);
    void CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, VkCommandPool commandPool, VkQueue queue);
    void CreateTextureImageView(uint32_t mipLevels, VkImage textureImage, VkImageView &textureImageView);
    VkImageView CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);
    void GenerateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels, VkCommandPool commandPool, VkQueue queue);
    static bool HasStencilComponent(VkFormat format);
    void TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, VkCommandPool commandPool, VkQueue queue);
    //endregion

    //region Command
    VkCommandBuffer BeginSingleTimeCommands(VkCommandPool commandPool);
    void EndSingleTimeCommands(VkCommandBuffer commandBuffer, VkCommandPool commandPool, VkQueue queue);
    void CreateCommandPool(VkCommandPool *commandPool);
    void CreateCommandBuffers();
    //endregion

    //region General
    void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer *buffer, VkDeviceMemory *bufferMemory);
    uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    //endregion

    //region DescriptorSets
    void CreateDescriptorSetLayout();
    void CreateDescriptorPool();
    void CreateDescriptorSets();
    //endregion

    //region UniformBuffers
    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
    //endregion

public:
    StarVulkan();
    void CreateInstance();

    GLFWwindow *window;

    //HELPERS
    bool CheckValidationSupport();
    static std::vector<const char*> GetRequiredExtensions();

};


#endif //STARENGINE_STARVULKAN_HPP
