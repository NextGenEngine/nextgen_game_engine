#include "components/rendering/api/vulkan/vulkan_vertex_buffer.h"

#include <vulkan/vulkan_core.h>

#include <cstring>
#include <iostream>

#include "components/rendering/api/vulkan/vulkan_buffer.h"
#include "components/rendering/api/vulkan/vulkan_context.h"

namespace nextgen::engine::rendering::vulkan {

VulkanVertexBuffer::VulkanVertexBuffer() {
  std::cout << "VulkanVertexBuffer object instantiated\n";
}

VulkanVertexBuffer::~VulkanVertexBuffer() {
  std::cout << "VulkanVertexBuffer instance destroyed\n";
}

void VulkanVertexBuffer::Initialize(VulkanContext& vulkan_context,
                                    VulkanBuffer& vulkan_buffer) {
  vulkan_context_ = &vulkan_context;
  vulkan_buffer_ = &vulkan_buffer;
  CreateVertexBuffer();
}

void VulkanVertexBuffer::Shutdown() const noexcept {
  if (vulkan_context_ == nullptr || vulkan_context_->device == nullptr) {
    std::cout
        << "VulkanVertexBuffer: Vulkan context or device is null; no need "
           "to cleanup swapchain\n";
    std::cout << "VulkanVertexBuffer: shutdown complete\n";
    return;
  }

  if (vulkan_context_->vertex_buffer != VK_NULL_HANDLE) {
    vkDestroyBuffer(vulkan_context_->device, vulkan_context_->vertex_buffer,
                    nullptr);
    vulkan_context_->vertex_buffer = VK_NULL_HANDLE;
    std::cout << "VulkanVertexBuffer: vertex_buffer destroyed\n";
  } else {
    std::cout
        << "VulkanVertexBuffer: vertex_buffer is null; no need to destroy it\n";
  }

  if (vulkan_context_->vertex_buffer_memory != VK_NULL_HANDLE) {
    vkFreeMemory(vulkan_context_->device, vulkan_context_->vertex_buffer_memory,
                 nullptr);
    vulkan_context_->vertex_buffer_memory = VK_NULL_HANDLE;
    std::cout << "VulkanVertexBuffer: vertex_buffer_memory got free\n";
  } else {
    std::cout << "VulkanVertexBuffer: vertex_buffer_memory is null; no need to "
                 "make it free\n";
  }

  std::cout << "VulkanVertexBuffer: shutdown complete\n";
}

void VulkanVertexBuffer::CreateVertexBuffer() const {
  VkDeviceSize const bufferSize =
      sizeof(vulkan_context_->vertices[0]) * vulkan_context_->vertices.size();

  VkBuffer stagingBuffer{};
  VkDeviceMemory stagingBufferMemory{};
  vulkan_buffer_->CreateBuffer(
      bufferSize, VulkanBuffer::BufferUsage{VK_BUFFER_USAGE_TRANSFER_SRC_BIT},
      VulkanBuffer::MemoryProperty{VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                                   VK_MEMORY_PROPERTY_HOST_COHERENT_BIT},
      stagingBuffer, stagingBufferMemory);

  void* data{};
  vkMapMemory(vulkan_context_->device, stagingBufferMemory, 0, bufferSize, 0,
              &data);
  memcpy(data, vulkan_context_->vertices.data(),
         static_cast<size_t>(bufferSize));
  vkUnmapMemory(vulkan_context_->device, stagingBufferMemory);

  vulkan_buffer_->CreateBuffer(
      bufferSize,
      VulkanBuffer::BufferUsage{VK_BUFFER_USAGE_TRANSFER_DST_BIT |
                                VK_BUFFER_USAGE_VERTEX_BUFFER_BIT},
      VulkanBuffer::MemoryProperty{VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT},
      vulkan_context_->vertex_buffer, vulkan_context_->vertex_buffer_memory);

  vulkan_buffer_->CopyBuffer(stagingBuffer, vulkan_context_->vertex_buffer,
                             bufferSize);

  vkDestroyBuffer(vulkan_context_->device, stagingBuffer, nullptr);
  vkFreeMemory(vulkan_context_->device, stagingBufferMemory, nullptr);
}

}  // namespace nextgen::engine::rendering::vulkan
