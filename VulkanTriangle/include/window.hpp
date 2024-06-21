// ================================================================================
// ================================================================================
// - File:    window.hpp
// - Purpose: This file contains various methods for implementing a window manager 
//            to support a Vulkan application
//
// Source Metadata
// - Author:  Jonathan A. Webb
// - Date:    June 19, 2024
// - Version: 1.0
// - Copyright: Copyright 2024, Jon Webb Inc.
// ================================================================================
// ================================================================================
// Include headers here

#ifndef window_HPP
#define window_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>
// ================================================================================
// ================================================================================ 

/**
 * @brief This class creates a template for other classes to follow that sets a 
 *        glfw like behavior for a window manager
 */
class Window {
public:

    /**
     * @brief This method should return true if the window is set to close, false otherwise
     */
    virtual bool windowShouldClose() = 0;
// --------------------------------------------------------------------------------

    /**
     * @brief This method is meant to register events interacting with the window
     */
    virtual void pollEvents() = 0; 
// --------------------------------------------------------------------------------

    virtual bool isInstance() = 0;
};
// ================================================================================
// ================================================================================


class GlfwWindow : public Window {
public:
   
    /*
     * @param h The window height in pixels
     * @param w The window width in pixels 
     * @param full_screen true if full screen, false otherwise.  Defaulted to false
     */
    GlfwWindow(uint32_t h, uint32_t w, const std::string& screen_title, bool full_screen = false);
    ~GlfwWindow();
// --------------------------------------------------------------------------------

    bool windowShouldClose() override;
// --------------------------------------------------------------------------------

    void pollEvents() override;
// --------------------------------------------------------------------------------

    bool isInstance() override;
// ================================================================================
private:
    GLFWwindow* window;
    bool glfw_terminated = false;
};
// ================================================================================
// ================================================================================ 

#endif /* file_name_HPP */
// ================================================================================
// ================================================================================
// eof
