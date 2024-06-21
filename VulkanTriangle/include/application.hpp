// ================================================================================
// ================================================================================
// - File:    application.hpp
// - Purpose: This file contains a basic application interface for building and 
//            displaying a triangle to the screen.
//
// Source Metadata
// - Author:  Jonathan A. Webb
// - Date:    June 19, 2024
// - Version: 1.0
// - Copyright: Copyright 2022, Jon Webb Inc.
// ================================================================================
// ================================================================================
// Include modules here

#ifndef application_HPP
#define application_HPP

#define GLFW_INCLUDE_VULKAN  // <vulkan/vulkan.h>
#include "window.hpp"
#include <iostream>
#include <vector>
#include <memory>
// ================================================================================
// ================================================================================


class CreateVulkanInstance {
public:
    virtual ~CreateVulkanInstance() = default;
    virtual VkInstance* getInstance() = 0;
};
// ================================================================================
// ================================================================================


class VulkanInstance : public CreateVulkanInstance {
public:
    VulkanInstance(Window &window);
// --------------------------------------------------------------------------------

    ~VulkanInstance() override;
// --------------------------------------------------------------------------------

    VkInstance* getInstance() override;
// ================================================================================
private:
    Window& window;
    VkInstance instance = VK_NULL_HANDLE;
// --------------------------------------------------------------------------------

    void createInstance();
};
// ================================================================================
// ================================================================================


/**
 * @brief This class represents the main application for rendering a triangle using Vulkan.
 * 
 * The HelloTriangleApplication class initializes the Vulkan context, manages the rendering loop,
 * and interacts with the window system through a Window interface.
 */

class HelloTriangleApplication {
public:
    /**
     * @brief Constructs a new HelloTriangleApplication instance.
     * 
     * @param window A reference to a Window object that the application will use.
     * @param vulkanInstanceCreator A reference to a CreateVulkanInstance object for creating the Vulkan instance.
     */
    HelloTriangleApplication(std::unique_ptr<Window> window, std::unique_ptr<CreateVulkanInstance> vulkanInstanceCreator);

    /**
     * @brief Destroys the HelloTriangleApplication instance.
     */
    ~HelloTriangleApplication();

    /**
     * @brief Runs the main application loop.
     * 
     * This method starts the main rendering loop of the application, polling window events
     * and rendering frames until the window is closed.
     */
    void run();

private:
    std::unique_ptr<Window> windowInstance;
    std::unique_ptr<CreateVulkanInstance> vulkanInstanceCreator;
// --------------------------------------------------------------------------------

    void destroyResources();
};
// ================================================================================
// ================================================================================

#endif /* file_name_HPP */
// ================================================================================
// ================================================================================
// eof
