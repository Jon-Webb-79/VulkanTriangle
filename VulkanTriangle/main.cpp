// ================================================================================
// ================================================================================
// - File:    main.cpp
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
#include "include/window.hpp"
#include "include/validation_layers.hpp"
#include "include/constants.hpp"
#include "include/graphics_pipeline.hpp"
#include <iostream>
#include <stdexcept>

int main(int argc, const char * argv[]) {
    try {
        std::unique_ptr<Window> window = std::make_unique<GlfwWindow>(650, 800, "Vulkan", false);
        auto validationLayers = std::make_unique<ValidationLayers>(window);
        std::unique_ptr<CreateVulkanInstance> vulkanInstanceCreator = std::make_unique<VulkanInstance>(window, validationLayers);
        auto physicalDevice = std::make_unique<VulkanPhysicalDevice>(*vulkanInstanceCreator->getInstance(), 
                                                                     vulkanInstanceCreator->getSurface());
        auto logicalDevice = std::make_unique<VulkanLogicalDevice>(physicalDevice->getPhysicalDevice(), 
                                                                   validationLayers->getValidationLayers(),
                                                                   vulkanInstanceCreator->getSurface(),
                                                                   deviceExtensions);
        auto swapChain = std::make_unique<SwapChain>(logicalDevice->getDevice(), 
                                                     vulkanInstanceCreator->getSurface(), 
                                                     physicalDevice->getPhysicalDevice(), 
                                                     window.get());
        auto pipeline = std::make_unique<GraphicsPipeline>(logicalDevice->getDevice(), 
                                                           swapChain->getSwapChainExtent(), 
                                                           swapChain->getSwapChainImageFormat());
        HelloTriangleApplication triangle(std::move(window), 
                                          std::move(vulkanInstanceCreator), 
                                          std::move(physicalDevice), 
                                          std::move(logicalDevice),
                                          std::move(swapChain),
                                          std::move(pipeline));
        triangle.run();
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
// ================================================================================
// ================================================================================
// eof
