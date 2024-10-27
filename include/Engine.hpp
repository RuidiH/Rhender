#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <vulkan/vulkan.h>
#include <string>
#include <memory>
#include <vector>

#include "Camera.hpp"
#include "EnginePipeline.hpp"
#include "EngineWindow.hpp"
#include "EngineDevice.hpp"
#include "EngineSwapChain.hpp"
#include "EngineModel.hpp"

namespace cgf
{
    class Engine
    {
    public:
        Engine();
        ~Engine();
        void Run();

        // delete copy/move constructors
        Engine(const Engine &) = delete;
        void operator=(const Engine &) = delete;

        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 600;

    private:
        void LoadModels();
        void CreatePipelineLayout();
        void CreatePipeline();
        void CreateCommandBuffers();
        void DrawFrame();
        void recreateSwapChain();
        void recordCommandBuffer(int imageIndex);

        EngineWindow mWindow{WIDTH, HEIGHT, "Vulkan Engine"};
        EngineDevice mEngineDevice{mWindow};
        std::unique_ptr<EngineSwapChain> mEngineSwapChain;
        std::unique_ptr<EnginePipeline> mEnginePipeline;
        VkPipelineLayout mPipelineLayout;
        std::vector<VkCommandBuffer> mCommandBuffers;
        std::unique_ptr<EngineModel> mEngineModel;

        void MainLoop();
        void Input();
        // void Update();
        void Render();
        void CleanUp();
        bool mIsRunning = true;
    };
}
#endif // ENGINE_HPP