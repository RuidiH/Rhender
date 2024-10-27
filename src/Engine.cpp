#include "Engine.hpp"

#include <stdexcept>
#include <array>

namespace cgf
{
    Engine::Engine()
    {
        LoadModels();
        CreatePipelineLayout();
        CreatePipeline();
        CreateCommandBuffers();
    }

    Engine::~Engine()
    {
        vkDestroyPipelineLayout(mEngineDevice.device(), mPipelineLayout, nullptr);
    }

    void Engine::Run()
    {
        MainLoop();
        CleanUp();
    }

    void Engine::LoadModels()
    {
        std::vector<EngineModel::Vertex> vertices {
            {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
            {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
            {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
        };

        mEngineModel = std::make_unique<EngineModel>(mEngineDevice, vertices);
    }

    void Engine::CreatePipelineLayout()
    {
        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 0;
        pipelineLayoutInfo.pSetLayouts = nullptr;

        // push constants
        pipelineLayoutInfo.pushConstantRangeCount = 0;

        if (vkCreatePipelineLayout(mEngineDevice.device(), &pipelineLayoutInfo, nullptr, &mPipelineLayout) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create pipeline layout!");
        }
    }

    void Engine::CreatePipeline()
    {
        auto pipelineConfig = EnginePipeline::DefaultPipelineConfigInfo(mEngineSwapChain.width(), mEngineSwapChain.height());
        pipelineConfig.renderPass = mEngineSwapChain.getRenderPass();
        pipelineConfig.pipelineLayout = mPipelineLayout;
        mEnginePipeline = std::make_unique<EnginePipeline>(
            mEngineDevice,
            "shaders/main_shader.vert.spv",
            "shaders/main_shader.frag.spv",
            pipelineConfig);
    }

    void Engine::CreateCommandBuffers()
    {
        mCommandBuffers.resize(mEngineSwapChain.imageCount());
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = mEngineDevice.getCommandPool();
        allocInfo.commandBufferCount = static_cast<uint32_t>(mCommandBuffers.size());

        if (vkAllocateCommandBuffers(mEngineDevice.device(), &allocInfo, mCommandBuffers.data()) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to allocate command buffers!");
        }

        for (int i = 0; i < mCommandBuffers.size(); i++)
        {
            VkCommandBufferBeginInfo beginInfo{};
            beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

            if (vkBeginCommandBuffer(mCommandBuffers[i], &beginInfo) != VK_SUCCESS)
            {
                throw std::runtime_error("failed to begin recording command buffer!");
            }
            VkRenderPassBeginInfo renderPassInfo{};
            renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            renderPassInfo.renderPass = mEngineSwapChain.getRenderPass();
            renderPassInfo.framebuffer = mEngineSwapChain.getFrameBuffer(i);
            renderPassInfo.renderArea.offset = {0, 0};
            renderPassInfo.renderArea.extent = mEngineSwapChain.getSwapChainExtent();

            std::array<VkClearValue, 2> clearValues{};
            clearValues[0].color = {0.1f, 0.1f, 0.1f, 1.0f};
            clearValues[1].depthStencil = {1.0f, 0};
            renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
            renderPassInfo.pClearValues = clearValues.data();

            vkCmdBeginRenderPass(mCommandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

            mEnginePipeline->Bind(mCommandBuffers[i]);
            // vkCmdDraw(mCommandBuffers[i], 3, 1, 0, 0);
            mEngineModel->Bind(mCommandBuffers[i]);
            mEngineModel->Draw(mCommandBuffers[i]);

            vkCmdEndRenderPass(mCommandBuffers[i]);
            if (vkEndCommandBuffer(mCommandBuffers[i]) != VK_SUCCESS)
            {
                throw std::runtime_error("failed to record command buffer!");
            }
        }
    }
    void Engine::DrawFrame() {
        uint32_t imageIndex;
        auto result = mEngineSwapChain.acquireNextImage(&imageIndex);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to acquire next image!");
        }

        result = mEngineSwapChain.submitCommandBuffers(&mCommandBuffers[imageIndex], &imageIndex);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to submit command buffer!");
        }

    }

    void Engine::Render()
    {
        DrawFrame();
    }

    void Engine::MainLoop()
    {
        while (mIsRunning)
        {
            Input();
            // Update();
            Render();
        }
        vkDeviceWaitIdle(mEngineDevice.device());
    }

    void Engine::Input()
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
            {
                mIsRunning = false;
            }
        }
    }

    void Engine::CleanUp()
    {
    }
}