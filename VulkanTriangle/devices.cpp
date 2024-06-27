// ================================================================================
// ================================================================================
// - File:    devices.cpp
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

#include "include/devices.hpp"
#include "include/queues.hpp"
#include <stdexcept>
#include <vector>
#include <set>
// ================================================================================
// ================================================================================

VulkanPhysicalDevice::VulkanPhysicalDevice(VkInstance& instance, VkSurfaceKHR surface) 
    : instance(instance), surface(surface) {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

    if (deviceCount == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    for (const auto& device : devices) {
        if (isDeviceSuitable(device)) {
            physicalDevice = device;
            break;
        }
    }

    if (physicalDevice == VK_NULL_HANDLE) {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
}
// --------------------------------------------------------------------------------

VkPhysicalDevice VulkanPhysicalDevice::getPhysicalDevice() const {
    return physicalDevice;
}
// --------------------------------------------------------------------------------

bool VulkanPhysicalDevice::isDeviceSuitable(const VkPhysicalDevice& device) {
    QueueFamilyIndices indices = QueueFamily::findQueueFamilies(device, surface);
    return indices.isComplete();
}
// ================================================================================ 
// ================================================================================

VulkanLogicalDevice::VulkanLogicalDevice(VkPhysicalDevice physicalDevice, 
                                         const std::vector<const char*>& validationLayers,
                                         VkSurfaceKHR surface)
    : physicalDevice(physicalDevice), 
      validationLayers(validationLayers),
      surface(surface){
    createLogicalDevice();
}
// --------------------------------------------------------------------------------

VulkanLogicalDevice::~VulkanLogicalDevice() {
    if (device != VK_NULL_HANDLE) {
        vkDestroyDevice(device, nullptr);
    }
}
// --------------------------------------------------------------------------------

VkDevice VulkanLogicalDevice::getDevice() const {
    return device;
}
// --------------------------------------------------------------------------------

VkQueue VulkanLogicalDevice::getGraphicsQueue() const {
    return graphicsQueue;
}
// ================================================================================

void VulkanLogicalDevice::createLogicalDevice() {
    QueueFamilyIndices indices = QueueFamily::findQueueFamilies(physicalDevice, surface);

    if (!indices.graphicsFamily.has_value() || !indices.presentFamily.has_value()) {
        throw std::runtime_error("Failed to find required queue families.");
    } 

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};

    float queuePriority = 1.0f;
    for (uint32_t queueFamily : uniqueQueueFamilies) {
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    VkPhysicalDeviceFeatures deviceFeatures{};

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    createInfo.pEnabledFeatures = &deviceFeatures;
    createInfo.enabledExtensionCount = 0;

    if (!validationLayers.empty()) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }

    if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
        throw std::runtime_error("failed to create logical device!");
    }

    vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
    vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &presentQueue);
}
// --------------------------------------------------------------------------------

// VulkanLogicalDevice::QueueFamilyIndices VulkanLogicalDevice::findQueueFamilies(VkPhysicalDevice device) {
//     QueueFamilyIndices indices;
//
//     uint32_t queueFamilyCount = 0;
//     vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
//
//     std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
//     vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
//
//     int i = 0;
//     for (const auto& queueFamily : queueFamilies) {
//         if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
//             indices.graphicsFamily = i;
//         }
//
//         if (indices.isComplete()) {
//             break;
//         }
//
//         i++;
//     }
//
//     return indices;
// }
// ================================================================================
// ================================================================================
// eof
