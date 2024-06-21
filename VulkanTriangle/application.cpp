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


HelloTriangleApplication::HelloTriangleApplication(Window& instance) {
    windowInstance = &instance;
}
// --------------------------------------------------------------------------------


HelloTriangleApplication::~HelloTriangleApplication() {
    tearDown();
}
// --------------------------------------------------------------------------------


void HelloTriangleApplication::run() {
    
    createInstance();

    while (!windowInstance->windowShouldClose()) {
        windowInstance->pollEvents();
    }
}
// ================================================================================ 


void HelloTriangleApplication::createInstance() {
    
    // Populate VkApplicationInfo struct to describe this application 
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "VulkanTriangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion= VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_MAKE_VERSION(1, 3, 279);

    // Variables used to helpf fined required extensions 
    uint32_t extensionCount = 0;
    const char** extensions;

    // Get list of required extensions as a pointer to a c-style array
    extensions = windowInstance->getRequiredInstanceExtensions(&extensionCount);

    // Implement VkInstanceCreateInfo struct 
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = extensionCount;
    createInfo.ppEnabledExtensionNames = extensions;
    createInfo.enabledLayerCount = 0;

    // Use data in createInfo struct to create a VkInstance
    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("Failed to Create Vulkan Instance!\n");
    }

    uint32_t newExtensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &newExtensionCount, nullptr);

    std::vector<VkExtensionProperties> newExtensions(newExtensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &newExtensionCount, newExtensions.data());

    std::cout << "Avialable Extensions:\n";

    for (const auto& extension : newExtensions) {
        std::cout << '\t' << extension.extensionName << '\n';
    }
}
// --------------------------------------------------------------------------------


void HelloTriangleApplication::tearDown() {
    if (instance != VK_NULL_HANDLE) {
        vkDestroyInstance(instance, nullptr);
        instance = VK_NULL_HANDLE;
    }
}
// ================================================================================
// ================================================================================
// eof
