#include "components/rendering/api/vulkan/vulkan_buffer.h"

#include <vulkan/vulkan_core.h>

#include <vector>

#include "components/rendering/api/vulkan/vulkan_context.h"

namespace nextgen::engine::rendering::vulkan {

void VulkanBuffer::Initialize(VulkanContext& vulkan_context) {
  vulkan_context_ = &vulkan_context;
}

struct Vertex {
  float pos[2];
  float color[3];
};

static std::vector<Vertex> vertices2 = {
    {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},  // Bottom left
    {{0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},   // Bottom right
    {{0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}},    // Top right
    {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},  // Bottom left
    {{0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}},    // Top right
    {{-0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}}    // Top left
};

uint32_t findMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter,
                        VkMemoryPropertyFlags properties) {
  VkPhysicalDeviceMemoryProperties memProperties;
  vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

  for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
    if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags &
                                    properties) == properties) {
      return i;
    }
  }

  throw std::runtime_error("failed to find suitable memory type!");
}

void VulkanBuffer::createVertexBuffer(VkDevice device,
                                      VkPhysicalDevice physicalDevice) {
  VkBufferCreateInfo bufferInfo{};
  bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  bufferInfo.size = sizeof(vertices2[0]) * vertices2.size();
  bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
  bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

  if (vkCreateBuffer(device, &bufferInfo, nullptr,
                     &vulkan_context_->vertexBuffer) != VK_SUCCESS) {
    throw std::runtime_error("failed to create vertex buffer!");
  }

  VkMemoryRequirements memRequirements;
  vkGetBufferMemoryRequirements(device, vulkan_context_->vertexBuffer,
                                &memRequirements);

  VkMemoryAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  allocInfo.allocationSize = memRequirements.size;
  allocInfo.memoryTypeIndex =
      findMemoryType(physicalDevice, memRequirements.memoryTypeBits,
                     VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                         VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

  if (vkAllocateMemory(device, &allocInfo, nullptr,
                       &vulkan_context_->vertexBufferMemory) != VK_SUCCESS) {
    throw std::runtime_error("failed to allocate vertex buffer memory!");
  }

  vkBindBufferMemory(device, vulkan_context_->vertexBuffer,
                     vulkan_context_->vertexBufferMemory, 0);

  void* data;
  vkMapMemory(device, vulkan_context_->vertexBufferMemory, 0, bufferInfo.size,
              0, &data);
  memcpy(data, vertices2.data(), (size_t)bufferInfo.size);
  vkUnmapMemory(device, vulkan_context_->vertexBufferMemory);
}

}  // namespace nextgen::engine::rendering::vulkan
