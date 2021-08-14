//
// Created by ReSung on 2021-08-14.
//

#ifndef STARENGINE_STARVULKAN_HPP
#define STARENGINE_STARVULKAN_HPP

#include <vulkan/vulkan.hpp>

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

class StarVulkan {
private:
    //OBJECTS
    VkInstance instance;

    //CONFIGURATION
    const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

public:
    StarVulkan();
    void CreateInstance();

    //HELPERS
    bool CheckValidationSupport();
    static std::vector<const char*> GetRequiredExtensions();
};


#endif //STARENGINE_STARVULKAN_HPP
