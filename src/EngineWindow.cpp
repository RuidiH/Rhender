#include "EngineWindow.hpp"

#include <iostream>
#include <stdexcept>

namespace cgf {

    EngineWindow::EngineWindow(int w, int h, std::string name) : mWidth(w), mHeight(h), mWindowName(name) {
        InitWindow(); 
    }

    EngineWindow::~EngineWindow() {
        SDL_DestroyWindow(mWindow);
        SDL_Quit();
    }

    void EngineWindow::InitWindow() {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            std::cerr << "Failed to initialize SDL!" << std::endl;
            exit(1);
        }

        mWindow = SDL_CreateWindow(mWindowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWidth, mHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_VULKAN);
        if (mWindow == nullptr) {
            std::cerr << "Failed to create window!" << std::endl;
            exit(1);
        }

        std::cout << "Window created!" << std::endl;
    }

    void EngineWindow::CreateWindowSurface(VkInstance instance, VkSurfaceKHR *surface) {
        if (SDL_Vulkan_CreateSurface(mWindow, instance, surface) == 0) {
            std::cerr << "Failed to create Vulkan surface!" << std::endl;
            exit(1);
        }
    }
} // namespace cgf