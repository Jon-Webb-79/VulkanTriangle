// ================================================================================
// ================================================================================
// - File:    queues.hpp
// - Purpose: Describe the file purpose here
//
// Source Metadata
// - Author:  Jonathan A. Webb
// - Date:    June 22, 2024
// - Version: 1.0
// - Copyright: Copyright 2022, Jon Webb Inc.
// ================================================================================
// ================================================================================
// Include modules here

#ifndef queues_HPP
#define queues_HPP

#include <vulkan/vulkan.h>
#include <optional>
// ================================================================================
// ================================================================================ 

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
// --------------------------------------------------------------------------------

    bool isComplete() const {
        return graphicsFamily.has_value();
    }
};
// ================================================================================
// ================================================================================

class QueueFamily {
public:
    static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
};
// ================================================================================
// ================================================================================

#endif /* queues_HPP */
// ================================================================================
// ================================================================================
// eof
