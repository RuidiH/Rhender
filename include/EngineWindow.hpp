#ifndef ENGINE_WINDOW_HPP
#define ENGINE_WINDOW_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>
#include <iostream>
#include <vulkan/vulkan.h>

namespace cgf {
    class EngineWindow {
        public:

            EngineWindow(int w, int h, std::string name);
            ~EngineWindow();

            void CreateWindowSurface(VkInstance instance, VkSurfaceKHR *surface);
            SDL_Window *GetWindow() { return mWindow; }

            // remove copy constructor
            EngineWindow(const EngineWindow &) = delete;
            EngineWindow &operator=(const EngineWindow &) = delete;

            VkExtent2D GetExtent() { return {static_cast<uint32_t>(mWidth), static_cast<uint32_t>(mHeight)}; }

            bool wasWindowResized() { return framebufferResized; }
            void resetWindowResizedFlag() { framebufferResized = false; }
            void framebufferResizeCallback();
        private:
            void InitWindow();

            int mWidth;
            int mHeight;
            bool framebufferResized = false;
            std::string mWindowName;
            SDL_Window *mWindow; 
    };
}

#endif // ENGINE_WINDOW_HPP