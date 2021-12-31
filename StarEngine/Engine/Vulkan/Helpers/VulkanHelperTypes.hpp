//
// Created by ReSung on 2021-12-31.
//

#ifndef B_OBJ_VULKANHELPERTYPES_HPP
#define B_OBJ_VULKANHELPERTYPES_HPP

#include <optional>

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    [[nodiscard]] bool isComplete() const {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

class VulkanHelperTypes {

};


#endif //B_OBJ_VULKANHELPERTYPES_HPP
