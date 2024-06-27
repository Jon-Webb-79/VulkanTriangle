// ================================================================================
// ================================================================================
// - File:    window.cpp
// - Purpose: Contains implementation for window.hpp file
//
// Source Metadata
// - Author:  Jonathan A. Webb
// - Date:    June 19, 2024
// - Version: 1.0
// - Copyright: Copyright 2024, Jon Webb Inc.
// ================================================================================
// ================================================================================
// Include modules here

#include "include/window.hpp"
#include <stdexcept>
// ================================================================================
// ================================================================================


GlfwWindow::GlfwWindow(uint32_t h, uint32_t w, const std::string& screen_title, bool full_screen) {
    if (!glfwInit()) {
        throw std::runtime_error("GLFW Initialization Failed!\n");
    }
    glfw_terminated = false;

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    GLFWmonitor* monitor = full_screen ? glfwGetPrimaryMonitor() : nullptr;

    window = glfwCreateWindow(w, h, screen_title.c_str(), monitor, nullptr);

    if (!window) {
        glfwTerminate();
        throw std::runtime_error("GLFW Instantiation failed!\n");
    }
}
// --------------------------------------------------------------------------------

GlfwWindow::~GlfwWindow() {
    if (window)
        glfwDestroyWindow(window);
    if (!glfw_terminated) {
        glfwTerminate();
        glfw_terminated = true;
    }
}
// --------------------------------------------------------------------------------

bool GlfwWindow::windowShouldClose() {
    return glfwWindowShouldClose(window);
}
// --------------------------------------------------------------------------------

void GlfwWindow::pollEvents() {
    return glfwPollEvents();
}
// --------------------------------------------------------------------------------

bool GlfwWindow::isInstance() {
    return glfw_terminated;
}
// --------------------------------------------------------------------------------

const char** GlfwWindow::getRequiredInstanceExtensions(uint32_t* count) {
    return glfwGetRequiredInstanceExtensions(count);
}
// --------------------------------------------------------------------------------


VkResult GlfwWindow::createWindowSurface(VkInstance instance,
                                         const VkAllocationCallbacks* allocator,
                                         VkSurfaceKHR* surface) {
    return glfwCreateWindowSurface(instance, window, allocator, surface);
}
// ================================================================================
// ================================================================================
// eof
