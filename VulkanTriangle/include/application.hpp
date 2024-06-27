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
#include "validation_layers.hpp"
#include "devices.hpp"

#include <iostream>
#include <vector>
#include <memory>
// ================================================================================
// ================================================================================


/**
 * @brief Abstract class to set interface for Vulkan Instance Creation
 */
class CreateVulkanInstance {
public:
    /**
     * @brief Desctructor
     */
    virtual ~CreateVulkanInstance() = default;
// --------------------------------------------------------------------------------

    /**
     * @brief Returns a raw pointer to the instance of Vulkan
     */
    virtual VkInstance* getInstance() = 0;
// --------------------------------------------------------------------------------

    /**
     * @brief Returns a raw pointer to an instance of surface
     */
    virtual VkSurfaceKHR getSurface() const = 0;
};
// ================================================================================
// ================================================================================


/**
 * @brief This class creates an instance of Vulkan to support an 
 * application that will draw a triangle to the screen
 */
class VulkanInstance : public CreateVulkanInstance {
public:
    /**
     * @brief Constructor for the VulkanInstance class 
     *
     * @param window A reference to a Window object
     */
    VulkanInstance(std::unique_ptr<Window>& window, std::unique_ptr<ValidationLayers>& validationLayers);
// --------------------------------------------------------------------------------

    /**
     * @brief Destructor for the VulkanInstance class
     */
    ~VulkanInstance() override;
// --------------------------------------------------------------------------------

    /**
     * @brief Returns a raw pointer to the instance of Vulkan
     */
    VkInstance* getInstance() override;
// --------------------------------------------------------------------------------

    /**
     * @brief Returns a raw pointer to an instance of surface
     */
    VkSurfaceKHR getSurface() const override;
// ================================================================================
private:
    std::unique_ptr<Window>& window;
    std::unique_ptr<ValidationLayers>& validationLayers;
    VkInstance instance = VK_NULL_HANDLE;
    VkSurfaceKHR surface;
// --------------------------------------------------------------------------------

    /**
     * @brief Helper function that allows the constructor to create a Vulkan instance
     */
    void createInstance();
// --------------------------------------------------------------------------------

    /**
     * @brief Helper function that establishes a relationship between Vulkan and the window
     */
    void createSurface();
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
    HelloTriangleApplication(std::unique_ptr<Window>& window, 
                             std::unique_ptr<CreateVulkanInstance>& vulkanInstanceCreator,
                             std::unique_ptr<VulkanPhysicalDevice>& physicalDevice,
                             std::unique_ptr<VulkanLogicalDevice>& logicalDevice);
// --------------------------------------------------------------------------------

    /**
     * @brief Destroys the HelloTriangleApplication instance.
     */
    ~HelloTriangleApplication();
// --------------------------------------------------------------------------------

    /**
     * @brief Runs the main application loop.
     * 
     * This method starts the main rendering loop of the application, polling window events
     * and rendering frames until the window is closed.
     */
    void run();
// ================================================================================
private:
    // Utilizing smart pointers so I can control the order of destruction
    std::unique_ptr<Window>& windowInstance;
    std::unique_ptr<CreateVulkanInstance>& vulkanInstanceCreator;
    std::unique_ptr<VulkanPhysicalDevice>& physicalDevice;
    std::unique_ptr<VulkanLogicalDevice>& logicalDevice;

    VkQueue graphicsQueue;
    VkQueue presentQueue;
// --------------------------------------------------------------------------------

    /**
     * @breif Helper function that allows the destructor to control the order 
     * of tear down
     */
    void destroyResources();
};
// ================================================================================
// ================================================================================

#endif /* file_name_HPP */
// ================================================================================
// ================================================================================
// eof
