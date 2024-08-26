#ifndef VULKAN_SHADER_HPP
#define VULKAN_SHADER_HPP

#include <string>
#include <vector>

#include <vulkan/vulkan.h>

#include "EngineDevice.hpp"
#include "EngineModel.hpp"

namespace cgf
{
    struct ShaderConfigInfo
    {
        VkViewport viewport;
        VkRect2D scissor;
        // VkPipelineViewportStateCreateInfo viewportInfo;
        VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
        VkPipelineRasterizationStateCreateInfo rasterizationInfo;
        VkPipelineMultisampleStateCreateInfo multisampleInfo;
        VkPipelineColorBlendAttachmentState colorBlendAttachment;
        VkPipelineColorBlendStateCreateInfo colorBlendInfo;
        VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
        VkPipelineLayout pipelineLayout = nullptr;
        VkRenderPass renderPass = nullptr;
        uint32_t subpass = 0;
    };

    class EnginePipeline
    {
    public:
        EnginePipeline(EngineDevice &device,
                     const char *vertexPath,
                     const char *fragmentPath,
                     const ShaderConfigInfo configInfo);
        ~EnginePipeline();

        EnginePipeline(const EnginePipeline &) = delete;
        void operator=(const EnginePipeline &) = delete;

        void Bind(VkCommandBuffer commandBuffer);

        static ShaderConfigInfo DefaultPipelineConfigInfo(uint32_t width, uint32_t height);

    private:
        static std::vector<char> ReadFile(const std::string &filePath);
        void CreateGraphicsPipeline(const char *vertexPath,
                                    const char *fragmentPath,
                                    const ShaderConfigInfo configInfo);

        void CreateShaderModule(const std::vector<char> &code, VkShaderModule *shaderModule);

        EngineDevice &device;
        VkPipeline graphicsPipeline;
        VkShaderModule vertexShaderModule;
        VkShaderModule fragmentShaderModule;
    };
}
#endif