#include "EngineModel.hpp"

#include <cassert>
#include <cstring>

namespace cgf
{
    EngineModel::EngineModel(EngineDevice &device, const std::vector<Vertex> &vertices) : mEngineDevice(device)
    {
        CreateVertexBuffer(vertices);
    }

    EngineModel::~EngineModel()
    {
        vkDestroyBuffer(mEngineDevice.device(), mVertexBuffer, nullptr);
        vkFreeMemory(mEngineDevice.device(), mVertexBufferMemory, nullptr);
    }

    void EngineModel::CreateVertexBuffer(const std::vector<Vertex> &vertices)
    {
        vertexCount = static_cast<uint32_t>(vertices.size());
        assert(vertexCount >= 3 && "Vertex count must be at least 3");
        VkDeviceSize buffersize = sizeof(vertices[0]) * vertexCount;
        mEngineDevice.createBuffer(
            buffersize,
            VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            mVertexBuffer,
            mVertexBufferMemory);

        void *data;
        vkMapMemory(
            mEngineDevice.device(),
            mVertexBufferMemory,
            0,
            buffersize,
            0,
            &data);
        memcpy(data, vertices.data(), static_cast<size_t>(buffersize));
        vkUnmapMemory(mEngineDevice.device(), mVertexBufferMemory);
    }

    void EngineModel::Bind(VkCommandBuffer commandBuffer)
    {
        VkBuffer buffers[] = {mVertexBuffer};
        VkDeviceSize offsets[] = {0};
        vkCmdBindVertexBuffers(commandBuffer, 0, 1, &mVertexBuffer, offsets);
    }

    void EngineModel::Draw(VkCommandBuffer commandBuffer)
    {   
        vkCmdDraw(
                commandBuffer, 
                vertexCount,    // vertex count
                1,              // instance count
                0,              // first vertex 
                0);            // first instance
    }

    std::vector<VkVertexInputBindingDescription> EngineModel::Vertex::getBindingDescriptions()
    {
        std::vector<VkVertexInputBindingDescription> bindingDescriptions(1);
        bindingDescriptions[0].binding = 0;
        bindingDescriptions[0].stride = sizeof(Vertex);
        bindingDescriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        return bindingDescriptions;
    }

    std::vector<VkVertexInputAttributeDescription> EngineModel::Vertex::getAttributeDescriptions()
    {
        std::vector<VkVertexInputAttributeDescription> attributeDescriptions(1);
        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[0].offset = 0;
        return attributeDescriptions;
    }

}
