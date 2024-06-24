// ================================================================================
// ================================================================================
// - File:    devices.hpp
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

#ifndef devices_HPP
#define devices_HPP

#include <vulkan/vulkan.h>
#include "queues.hpp"
#include <memory>
#include <vector>
// ================================================================================
// ================================================================================ 

/**
 * @class VulkanPhysicalDevice
 * @brief Represents a physical device in a Vulkan application.
 * 
 * This class is responsible for selecting a suitable physical device (GPU) from the available devices
 * that support Vulkan. It checks if the device is suitable based on specific criteria.
 */
class VulkanPhysicalDevice {
public:
    /**
     * @brief Constructs a VulkanPhysicalDevice object.
     * 
     * This constructor initializes the VulkanPhysicalDevice by selecting a suitable physical device
     * from the available devices that support Vulkan.
     * 
     * @param instance A reference to the Vulkan instance.
     */
    VulkanPhysicalDevice(VkInstance& instance);
// --------------------------------------------------------------------------------

    /**
     * @brief Retrieves the selected physical device.
     * 
     * @return The Vulkan physical device handle.
     */
    VkPhysicalDevice getPhysicalDevice() const;
// ================================================================================

private:
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkInstance& instance;
// --------------------------------------------------------------------------------
    
    /**
     * @brief Checks if a physical device is suitable for the application.
     * 
     * @param device The Vulkan physical device to check.
     * @return True if the device is suitable, false otherwise.
     */
    bool isDeviceSuitable(const VkPhysicalDevice& device);
};
// ================================================================================
// ================================================================================

/**
 * @class VulkanLogicalDevice
 * @brief Represents a logical device in a Vulkan application.
 * 
 * This class is responsible for creating and managing a logical device (VkDevice) and its associated
 * graphics queue. It requires a physical device and optionally validation layers.
 */
class VulkanLogicalDevice {
public:
    
    /**
     * @brief Constructs a VulkanLogicalDevice object.
     * 
     * This constructor initializes the VulkanLogicalDevice by creating a logical device and its
     * associated graphics queue.
     * 
     * @param physicalDevice A reference to the Vulkan physical device.
     * @param validationLayers A vector containing the names of the validation layers to be enabled.
     */
    VulkanLogicalDevice(VkPhysicalDevice physicalDevice, const std::vector<const char*>& validationLayers);
// --------------------------------------------------------------------------------
    
    /**
     * @brief Destroys the VulkanLogicalDevice object.
     * 
     * This destructor cleans up the logical device by destroying it if it has been created.
     */
    ~VulkanLogicalDevice();
// --------------------------------------------------------------------------------
    
    /**
     * @brief Retrieves the logical device.
     * 
     * @return The Vulkan logical device handle.
     */
    VkDevice getDevice() const;
// --------------------------------------------------------------------------------

    /**
     * @brief Retrieves the graphics queue.
     * 
     * @return The Vulkan graphics queue handle.
     */
    VkQueue getGraphicsQueue() const;
// ================================================================================
private:
    VkDevice device = VK_NULL_HANDLE;
    VkQueue graphicsQueue;
    VkPhysicalDevice physicalDevice;  // Changed to reference
    const std::vector<const char*>& validationLayers;
// --------------------------------------------------------------------------------

    // Queue family indices struct
    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        bool isComplete() const {
            return graphicsFamily.has_value();
        }
    };
// --------------------------------------------------------------------------------

    /**
     * @brief Creates the logical device and retrieves the graphics queue.
     */
    void createLogicalDevice();
// --------------------------------------------------------------------------------

    /**
     * @brief Finds the queue families that support the required operations.
     * 
     * @param device The Vulkan physical device to query.
     * @return A QueueFamilyIndices struct containing the indices of the required queue families.
     */
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);  // Add declaration
};
// ================================================================================
// ================================================================================ 
#endif /* devices_HPP */
// ================================================================================
// ================================================================================
// eof
