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

VulkanInstance::VulkanInstance(std::unique_ptr<Window>& window, std::unique_ptr<ValidationLayers>& validationLayers)
    : window(window), validationLayers(validationLayers) {
    createInstance();
    createSurface();
}
// --------------------------------------------------------------------------------


VulkanInstance::~VulkanInstance() {
    if (surface != VK_NULL_HANDLE) {
        vkDestroySurfaceKHR(instance, surface, nullptr);
    }

    if (instance != VK_NULL_HANDLE) {
        validationLayers->cleanup(instance);
        vkDestroyInstance(instance, nullptr);
    }
}
// --------------------------------------------------------------------------------


VkInstance* VulkanInstance::getInstance() {
    return &instance;
}
// --------------------------------------------------------------------------------

VkSurfaceKHR VulkanInstance::getSurface() const {
    return surface;
}
// ================================================================================


void VulkanInstance::createInstance() {
    if (validationLayers->isEnabled() && !validationLayers->checkValidationLayerSupport()) {
        throw std::runtime_error("validation layers requested, but not available!");
    }

    // Populate VkApplicationInfo struct to describe this application
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "VulkanTriangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_3;

    // Variables used to help find required extensions
    uint32_t extensionCount = 0;
    const char** extensions = window->getRequiredInstanceExtensions(&extensionCount);
    std::vector<const char*> extensionVector(extensions, extensions + extensionCount);

    // If validation layers are enabled, add their required extensions
    if (validationLayers->isEnabled()) {
        std::vector<const char*> validationLayerExtensions = validationLayers->getRequiredExtensions();
        extensionVector.insert(extensionVector.end(), validationLayerExtensions.begin(), validationLayerExtensions.end());
    }

    // Implement VkInstanceCreateInfo struct
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensionVector.size());
    createInfo.ppEnabledExtensionNames = extensionVector.data();

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
    if (validationLayers->isEnabled()) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers->getValidationLayers().size());
        createInfo.ppEnabledLayerNames = validationLayers->getValidationLayers().data(); 
        validationLayers->populateDebugMessengerCreateInfo(debugCreateInfo);
        createInfo.pNext = &debugCreateInfo;
    } else {
        createInfo.enabledLayerCount = 0;
        createInfo.ppEnabledLayerNames = nullptr;
        createInfo.pNext = nullptr;
    }

    // Create the Vulkan instance
    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("Failed to Create Vulkan Instance!");
    }

    if (validationLayers->isEnabled()) {
        validationLayers->setupDebugMessenger(instance);
    }
}
// --------------------------------------------------------------------------------

void VulkanInstance::createSurface() {
    if (window->createWindowSurface(instance, nullptr, &surface) != VK_SUCCESS)
        throw std::runtime_error("Failed to create window surface\n");
}
// ================================================================================
// ================================================================================

HelloTriangleApplication::HelloTriangleApplication(std::unique_ptr<Window>& window,
                                                   std::unique_ptr<CreateVulkanInstance>& vulkanInstanceCreator,
                                                   std::unique_ptr<VulkanPhysicalDevice>& physicalDevice,
                                                   std::unique_ptr<VulkanLogicalDevice>& logicalDevice,
                                                   std::unique_ptr<SwapChain>& swapChain)
    : windowInstance(window), 
      vulkanInstanceCreator(vulkanInstanceCreator), 
      physicalDevice(physicalDevice),
      logicalDevice(logicalDevice),
      swapChain(swapChain){}
// --------------------------------------------------------------------------------

HelloTriangleApplication::~HelloTriangleApplication() {
    destroyResources();
}
// --------------------------------------------------------------------------------

void HelloTriangleApplication::run() {
    while (!windowInstance->windowShouldClose()) {
        windowInstance->pollEvents();
    }
}
// --------------------------------------------------------------------------------

void HelloTriangleApplication::destroyResources() {
    // Destroy Vulkan instance before the window
    swapChain.reset();
    logicalDevice.reset();
    physicalDevice.reset();
    vulkanInstanceCreator.reset();
    windowInstance.reset();
}
// ================================================================================
// ================================================================================
// eof
