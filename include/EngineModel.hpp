#pragma once

#include "EngineDevice.hpp"


#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <vector>

namespace cgf {
    class EngineModel {
        public:

            struct Vertex {
                glm::vec2 position;

                static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
                static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
            };


            EngineModel(EngineDevice &device, const std::vector<Vertex> &vertices);
            ~EngineModel();

            EngineModel(const EngineModel &) = delete;
            EngineModel &operator=(const EngineModel &) = delete; 

            void Bind(VkCommandBuffer commandBuffer);
            void Draw(VkCommandBuffer commandBuffer);

        private:
            void CreateVertexBuffer(const std::vector<Vertex> &vertices);

            EngineDevice& mEngineDevice;
            VkBuffer mVertexBuffer;
            VkDeviceMemory mVertexBufferMemory;
            uint32_t vertexCount; 

    };
}