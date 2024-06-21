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

#include "window.hpp"
#include <iostream>
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
     * @param instance A reference to a Window object that the application will use.
     */
    HelloTriangleApplication(Window& instance);
// --------------------------------------------------------------------------------
    
    /**
     * @brief Destroys the HelloTriangleApplication instance.
     */
    ~HelloTriangleApplication() = default;
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

    /**
     * @brief A pointer to the Window instance used by the application.
     * 
     * The windowInstance attribute holds a reference to the Window object, allowing the application
     * to interact with the window system for event polling and checking if the window should close.
     */
    Window* windowInstance;
};
// ================================================================================
// ================================================================================

#endif /* file_name_HPP */
// ================================================================================
// ================================================================================
// eof
