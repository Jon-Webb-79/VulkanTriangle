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
 * @brief This abstract base class defines the interface for a window manager.
 * 
 * The Window class provides a standard interface for window management, including methods
 * for checking if the window should close, polling events, and checking the instance state.
 * Derived classes must implement these methods.
 */
class Window {
public:
    
    /**
     * @brief Checks if the window should close.
     * 
     * This pure virtual method must be implemented by derived classes to determine
     * whether the window should close.
     * 
     * @return true if the window should close, false otherwise.
     */
    virtual bool windowShouldClose() = 0;
// --------------------------------------------------------------------------------

    /**
     * @brief Polls events for the window.
     * 
     * This pure virtual method must be implemented by derived classes to handle
     * event polling for the window system.
     */
    virtual void pollEvents() = 0; 
// --------------------------------------------------------------------------------
    
    /**
     * @brief Checks if the window instance is valid.
     * 
     * This pure virtual method must be implemented by derived classes to determine
     * if the window instance is valid or has been properly initialized.
     * 
     * @return true if the window instance is valid, false otherwise.
     */
    virtual bool isInstance() = 0;
// --------------------------------------------------------------------------------

    /**
    * @brief Abstract method to retrieve the required instance extensions for the window manager.
    * 
    * This method should be implemented by derived classes to return the instance extensions
    * required by the window manager for Vulkan to interface with the windowing system.
    * 
    * @param[out] count Pointer to an unsigned integer where the number of extensions will be stored.
    * @return const char** An array of strings containing the names of the required extensions.
    */
    virtual const char** getRequiredInstanceExtensions(uint32_t* count) = 0;
};
// ================================================================================
// ================================================================================


class GlfwWindow : public Window {
public:
  
    /**
     * @brief Constructs a new GlfwWindow instance.
     * 
     * Initializes GLFW, creates a window, and sets it up with the specified dimensions,
     * title, and fullscreen mode.
     * 
     * @param h The height of the window in pixels.
     * @param w The width of the window in pixels.
     * @param screen_title The title of the window.
     * @param full_screen Whether the window should be fullscreen. Default is false.
     */ 
    GlfwWindow(uint32_t h, uint32_t w, const std::string& screen_title, bool full_screen = false);
// --------------------------------------------------------------------------------

    /**
     * @brief Destroys the GlfwWindow instance.
     * 
     * Destroys the GLFW window and terminates GLFW if it was not already terminated.
     */
    ~GlfwWindow();
// --------------------------------------------------------------------------------

    /**
     * @brief Checks if the GLFW window should close.
     * 
     * @return true if the window should close, false otherwise.
     */
    bool windowShouldClose() override;
// --------------------------------------------------------------------------------
    
    /**
     * @brief Polls events for the GLFW window.
     */
    void pollEvents() override;
// --------------------------------------------------------------------------------

    /**
     * @brief Checks if GLFW has been terminated.
     * 
     * @return true if GLFW has been terminated, false otherwise.
     */
    bool isInstance() override;
// --------------------------------------------------------------------------------

    /**
    * @brief Retrieve the required instance extensions for GLFW.
    * 
    * This method calls glfwGetRequiredInstanceExtensions to get the instance extensions
    * required by GLFW for Vulkan to interface with the windowing system.
    * 
    * @param[out] count Pointer to an unsigned integer where the number of extensions will be stored.
    * @return const char** An array of strings containing the names of the required extensions.
    */
    const char** getRequiredInstanceExtensions(uint32_t* count) override;
// ================================================================================
private:

    /**
     * @brief Pointer to the GLFW window instance.
     */
    GLFWwindow* window;
    
    /**
     * @brief Indicates whether GLFW has been terminated.
     */
    bool glfw_terminated = false;
};
// ================================================================================
// ================================================================================ 

#endif /* file_name_HPP */
// ================================================================================
// ================================================================================
// eof
