// ================================================================================
// ================================================================================
// - File:    application.cpp
// - Purpose: Describe the file purpose here
//
// Source Metadata
// - Author:  Jonathan A. Webb
// - Date:    June 19, 2024
// - Version: 1.0
// - Copyright: Copyright 2022, Jon Webb Inc.
// ================================================================================
// ================================================================================
// Include modules here

#include "include/application.hpp"
#include <vector>
#include <iostream>
// ================================================================================
// ================================================================================


VulkanInstance::VulkanInstance(Window& window) : window(window) {
    createInstance(); 
}
// --------------------------------------------------------------------------------


VulkanInstance::~VulkanInstance() {
    if (instance != VK_NULL_HANDLE) {
        vkDestroyInstance(instance, nullptr);
    }
}
// --------------------------------------------------------------------------------


VkInstance* VulkanInstance::getInstance() {
    return &instance;
}
// ================================================================================


void VulkanInstance::createInstance() {
    // Populate VkApplicationInfo struct to describe this application
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "VulkanTriangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_MAKE_VERSION(1, 3, 279);

    // Variables used to help find required extensions
    uint32_t extensionCount = 0;
    const char** extensions = window.getRequiredInstanceExtensions(&extensionCount);

    // Implement VkInstanceCreateInfo struct
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = extensionCount;
    createInfo.ppEnabledExtensionNames = extensions;
    createInfo.enabledLayerCount = 0;

    // Create the Vulkan instance
    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("Failed to Create Vulkan Instance!");
    }
}
// ================================================================================
// ================================================================================

HelloTriangleApplication::HelloTriangleApplication(std::unique_ptr<Window> window, std::unique_ptr<CreateVulkanInstance> vulkanInstanceCreator)
    : windowInstance(std::move(window)), vulkanInstanceCreator(std::move(vulkanInstanceCreator)) {
    // Vulkan instance is created in the VulkanInstance constructor
}
// --------------------------------------------------------------------------------

HelloTriangleApplication::~HelloTriangleApplication() {
    // Vulkan instance is destroyed in the VulkanInstance destructor
}

void HelloTriangleApplication::run() {
    while (!windowInstance->windowShouldClose()) {
        windowInstance->pollEvents();
    }
}
// ================================================================================

void HelloTriangleApplication::destroyResources() {
    // Destroy Vulkan instance before the window
    vulkanInstanceCreator.reset();
    windowInstance.reset();
}
// ================================================================================
// ================================================================================
// eof
