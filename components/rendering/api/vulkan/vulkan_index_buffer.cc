#include "components/rendering/api/vulkan/vulkan_index_buffer.h"

#include <vulkan/vulkan_core.h>

#include <cstring>
#include <iostream>

#include "components/rendering/api/vulkan/vulkan_buffer.h"
#include "components/rendering/api/vulkan/vulkan_context.h"

namespace nextgen::engine::rendering::vulkan {

VulkanIndexBuffer::VulkanIndexBuffer() {
  std::cout << "VulkanIndexBuffer object instantiated\n";
}

VulkanIndexBuffer::~VulkanIndexBuffer() {
  std::cout << "VulkanIndexBuffer instance destroyed\n";
}

void VulkanIndexBuffer::Initialize(VulkanContext& vulkan_context,
                                   VulkanBuffer& vulkan_buffer) {
  vulkan_context_ = &vulkan_context;
  vulkan_buffer_ = &vulkan_buffer;
  CreateIndexBuffer();
}

void VulkanIndexBuffer::Shutdown() const noexcept {
  if (vulkan_context_ == nullptr || vulkan_context_->device == nullptr) {
    std::cout << "VulkanIndexBuffer: Vulkan context or device is null; no need "
                 "to cleanup swapchain\n";
    std::cout << "VulkanIndexBuffer: shutdown complete\n";
    return;
  }

  if (vulkan_context_->index_buffer != VK_NULL_HANDLE) {
    vkDestroyBuffer(vulkan_context_->device, vulkan_context_->index_buffer,
                    nullptr);
    vulkan_context_->index_buffer = VK_NULL_HANDLE;
    std::cout << "VulkanIndexBuffer: index_buffer destroyed\n";
  } else {
    std::cout
        << "VulkanIndexBuffer: index_buffer is null; no need to destroy it\n";
  }

  if (vulkan_context_->index_buffer_memory != VK_NULL_HANDLE) {
    vkFreeMemory(vulkan_context_->device, vulkan_context_->index_buffer_memory,
                 nullptr);
    vulkan_context_->index_buffer_memory = VK_NULL_HANDLE;
    std::cout << "VulkanIndexBuffer: index_buffer_memory got free\n";
  } else {
    std::cout << "VulkanIndexBuffer: index_buffer_memory is null; no need to "
                 "make it free\n";
  }

  std::cout << "VulkanIndexBuffer: shutdown complete\n";
}

void VulkanIndexBuffer::CreateIndexBuffer() const {
  VkDeviceSize const bufferSize =
      sizeof(vulkan_context_->indices[0]) * vulkan_context_->indices.size();

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
  memcpy(data, vulkan_context_->indices.data(),
         static_cast<size_t>(bufferSize));
  vkUnmapMemory(vulkan_context_->device, stagingBufferMemory);

  vulkan_buffer_->CreateBuffer(
      bufferSize,
      VulkanBuffer::BufferUsage{VK_BUFFER_USAGE_TRANSFER_DST_BIT |
                                VK_BUFFER_USAGE_INDEX_BUFFER_BIT},
      VulkanBuffer::MemoryProperty{VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT},
      vulkan_context_->index_buffer, vulkan_context_->index_buffer_memory);

  vulkan_buffer_->CopyBuffer(stagingBuffer, vulkan_context_->index_buffer,
                             bufferSize);

  vkDestroyBuffer(vulkan_context_->device, stagingBuffer, nullptr);
  vkFreeMemory(vulkan_context_->device, stagingBufferMemory, nullptr);
}

}  // namespace nextgen::engine::rendering::vulkan
