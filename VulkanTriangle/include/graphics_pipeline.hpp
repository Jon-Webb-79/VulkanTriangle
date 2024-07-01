// ================================================================================
// ================================================================================
// - File:    graphics_pipeline.hpp
// - Purpose: Describe the file purpose here
//
// Source Metadata
// - Author:  Jonathan A. Webb
// - Date:    June 30, 2024
// - Version: 1.0
// - Copyright: Copyright 2022, Jon Webb Inc.
// ================================================================================
// ================================================================================
// Include modules here

#ifndef graphics_pipeline_HPP
#define graphics_pipeline_HPP

#include <vulkan/vulkan.h>
#include <vector>
#include <string>
// ================================================================================
// ================================================================================

class GraphicsPipeline {
public:
    GraphicsPipeline(VkDevice device, VkExtent2D swapChainExtent, VkFormat swapChainImageFormat);
// --------------------------------------------------------------------------------

    ~GraphicsPipeline();
// --------------------------------------------------------------------------------

    VkPipeline getPipeline() const;
// --------------------------------------------------------------------------------

    VkPipelineLayout getPipelineLayout() const;
// ================================================================================
private:
    VkDevice device;
    VkPipeline graphicsPipeline;
    VkPipelineLayout pipelineLayout;
    VkRenderPass renderPass;
// --------------------------------------------------------------------------------

    VkShaderModule createShaderModule(const std::vector<char>& code);
// --------------------------------------------------------------------------------

    std::vector<char> readFile(const std::string& filename);
// --------------------------------------------------------------------------------

    void createGraphicsPipeline(VkExtent2D swapChainExtent, VkFormat swapChainImageFormat);
// --------------------------------------------------------------------------------

    void createRenderPass(VkFormat swapChainImageFormat);
};
// ================================================================================
// ================================================================================

#endif /* graphics_pipeline_HPP */
// ================================================================================
// ================================================================================
// eof
