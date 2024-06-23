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
#include <iostream>
#include <stdexcept>

int main(int argc, const char * argv[]) {
    try {
        auto window = std::make_unique<GlfwWindow>(650, 800, "Vulkan", false);
        auto validationLayers = std::make_unique<ValidationLayers>(window.get());
        std::unique_ptr<CreateVulkanInstance> vulkanInstanceCreator = std::make_unique<VulkanInstance>(*window, *validationLayers);
        HelloTriangleApplication triangle(std::move(window), std::move(vulkanInstanceCreator));
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

