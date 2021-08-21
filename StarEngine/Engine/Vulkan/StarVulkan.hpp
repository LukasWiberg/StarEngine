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

        [[nodiscard]] bool isComplete() const {
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
    VkInstance instance{};
    VkSurfaceKHR surface{};
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_1_BIT;
    VkRenderPass renderPass{};
    uint32_t elementCount = 51200;

    TextureObject mainTex{};

    //region SwapChainObjects
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat{};
    std::vector<VkImageView> swapChainImageViews;
    std::vector<VkFramebuffer> swapChainFrameBuffers;
    //endregion

    //region Command
    VkCommandPool mainCommandPool{};
    //endregion

    //region PipelineObjects
    VkPipelineLayout pipelineLayout{};
    VkPipeline graphicsPipeline{};
    //endregion

    std::vector<uint32_t> indices;
    VkBuffer vertexBuffer = VK_NULL_HANDLE;
    VkBuffer indexBuffer = VK_NULL_HANDLE;
    VkDeviceMemory indexBufferMemory{};
    //endregion

    //region SwapChain
    VkSampler textureSampler{};
    //endregion

    //region DescriptorSets
    VkDescriptorPool descriptorPool{};
    VkDescriptorSetLayout descriptorSetLayout{};
    std::vector<VkDescriptorSet> descriptorSets;
    //endregion

    //region Depth
    VkImage depthImage{};
    VkDeviceMemory depthImageMemory{};
    VkImageView depthImageView{};
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
    bool IsDeviceSuitable(VkPhysicalDevice physDevice);
    StarVulkan::QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice physDevice);
    bool CheckDeviceExtensionSupport(VkPhysicalDevice physDevice);
    StarVulkan::SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice physDevice);
    //endregion

    //region LogicalDevice
    void CreateLogicalDevice();
    //endregion

    //region SwapChain
    void CreateSwapChain();
    void CreateSwapChainImages();
    static VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    static VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    [[nodiscard]] VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) const;
    //endregion

    //region Texture
    StarVulkan::TextureObject CreateTexture(char *path, bool generateMipMaps, VkCommandPool commandPool, VkQueue queue);
    void CreateTextureImage(char* path, bool generateMipmaps, uint32_t& mipLevels, VkImage& textureImage, VkDeviceMemory& textureImageMemory, VkCommandPool commandPool, VkQueue queue);
    void CreateImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage *image, VkDeviceMemory *imageMemory);
    void CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, VkCommandPool commandPool, VkQueue queue);
    void CreateTextureImageView(uint32_t mipLevels, VkImage textureImage, VkImageView &textureImageView);
    VkImageView CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels) const;
    void GenerateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels, VkCommandPool commandPool, VkQueue queue);
    static bool HasStencilComponent(VkFormat format);
    void TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, VkCommandPool commandPool, VkQueue queue);
    VkFormat FindDepthFormat();
    VkFormat FindSupportedFormat(VkFormat *candidates, uint32_t candidateCount, VkImageTiling tiling, VkFormatFeatureFlags features);
    //endregion

    //region Command
    VkCommandBuffer BeginSingleTimeCommands(VkCommandPool commandPool) const;
    void EndSingleTimeCommands(VkCommandBuffer commandBuffer, VkCommandPool commandPool, VkQueue queue) const;
    void CreateCommandPool(VkCommandPool &commandPool);
    void CreateCommandBuffers();
    //endregion

    //region General
    void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    //endregion

    //region DescriptorSets
    void CreateDescriptorSetLayout();
    void CreateDescriptorPool();
    void CreateDescriptorSets();
    //endregion

    //region UniformBuffers
    std::vector<VkBuffer> uniformBuffers;
    //endregion

    //region RenderPass
    void CreateRenderPass();
    //endregion

    //region GraphicsPipeline
    void CreateGraphicsPipeline();
    //endregion

    //region Shader
    VkShaderModule CreateShaderModule(const uint32_t *code, uint32_t codeSize) const;
    //endregion

    //region Depth
    void CreateDepthResources();
    //endregion

    //region FrameBuffer
    void CreateFrameBuffers();
    //endregion

    //region TextureSampler
    void CreateTextureSampler();
    //endregion

    //region Model
    void GetModel();
    //endregion

    //region IndexBuffer
    void CreateIndexBuffer();
    //endregion

    //region Buffer
    void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    //endregion

    //region UniformBuffer
    void CreateUniformBuffers();
    //endregion

    //region SyncObjects
    void CreateSyncObjects();
    //endregion

    static void FramebufferResizeCallback(GLFWwindow* glfwWindow, int width, int height);

public:
    StarVulkan();
    void CreateInstance();

    GLFWwindow *window{};
    VkDevice device{};
    std::vector<VkCommandBuffer> commandBuffers;
    VkSwapchainKHR swapChain{};
    VkQueue graphicsQueue{}, presentQueue{};
    VkExtent2D swapChainExtent{};
    std::vector<VkDeviceMemory> uniformBuffersMemory;
    VkDeviceMemory vertexBufferMemory{};


    //region SyncObjects
    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    std::vector<VkFence> imagesInFlight;
    //endregion

    //HELPERS
    bool CheckValidationSupport();
    static std::vector<const char*> GetRequiredExtensions();

    //region Cleanup/Recreate
    void RecreateSwapChain();
    void CleanupSwapChain();
    void Cleanup();
    //endregion

    //region VertexBuffer
    void CreateVertexBuffer();
    //endregion

//region VertexObjects
std::vector<Vertex> vertices;
};


#endif //STARENGINE_STARVULKAN_HPP
