#include "components/rendering/api/vulkan/vulkan_uniform_buffer.h"

#include <vulkan/vulkan_core.h>

#include <cstring>
#include <iostream>

#include "components/rendering/api/vulkan/vulkan_buffer.h"
#include "components/rendering/api/vulkan/vulkan_constants.h"
#include "components/rendering/api/vulkan/vulkan_context.h"

namespace nextgen::engine::rendering::vulkan {

VulkanUniformBuffer::VulkanUniformBuffer() {
  std::cout << "VulkanUniformBuffer object instantiated\n";
}

VulkanUniformBuffer::~VulkanUniformBuffer() {
  std::cout << "VulkanUniformBuffer instance destroyed\n";
}

void VulkanUniformBuffer::Initialize(VulkanContext& vulkan_context,
                                     VulkanBuffer& vulkan_buffer) {
  vulkan_context_ = &vulkan_context;
  vulkan_buffer_ = &vulkan_buffer;
  CreateUniformBuffers();
}

void VulkanUniformBuffer::Shutdown() const noexcept {
  if (vulkan_context_ == nullptr || vulkan_context_->device == nullptr) {
    std::cout
        << "VulkanUniformBuffer: Vulkan context or device is null; no need "
           "to cleanup swapchain\n";
    std::cout << "VulkanUniformBuffer: shutdown complete\n";
    return;
  }

  for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
    if (vulkan_context_->uniform_buffers[i] != VK_NULL_HANDLE) {
      vkDestroyBuffer(vulkan_context_->device,
                      vulkan_context_->uniform_buffers[i], nullptr);
      vulkan_context_->uniform_buffers[i] = VK_NULL_HANDLE;
      std::cout << "VulkanUniformBuffer: uniform_buffers[" << i
                << "] destroyed\n";
    } else {
      std::cout << "VulkanUniformBuffer: uniform_buffers[" << i
                << "] is null; no need to "
                   "destroy it\n";
    }

    if (vulkan_context_->uniform_buffers_memory[i] != VK_NULL_HANDLE) {
      vkFreeMemory(vulkan_context_->device,
                   vulkan_context_->uniform_buffers_memory[i], nullptr);
      vulkan_context_->uniform_buffers_memory[i] = VK_NULL_HANDLE;
      std::cout << "VulkanUniformBuffer: uniform_buffers_memory[" << i
                << "] got free\n";
    } else {
      std::cout << "VulkanUniformBuffer: uniform_buffers_memory[" << i
                << "] is null; no need to "
                   "make it free\n";
    }
  }

  std::cout << "VulkanUniformBuffer: shutdown complete\n";
}

void VulkanUniformBuffer::CreateUniformBuffers() const {
  VkDeviceSize const bufferSize = sizeof(UniformBufferObject);

  vulkan_context_->uniform_buffers.resize(MAX_FRAMES_IN_FLIGHT);
  vulkan_context_->uniform_buffers_memory.resize(MAX_FRAMES_IN_FLIGHT);
  vulkan_context_->uniform_buffers_mapped.resize(MAX_FRAMES_IN_FLIGHT);

  for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
    vulkan_buffer_->CreateBuffer(
        bufferSize,
        VulkanBuffer::BufferUsage{VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT},
        VulkanBuffer::MemoryProperty{VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                                     VK_MEMORY_PROPERTY_HOST_COHERENT_BIT},
        vulkan_context_->uniform_buffers[i],
        vulkan_context_->uniform_buffers_memory[i]);

    vkMapMemory(vulkan_context_->device,
                vulkan_context_->uniform_buffers_memory[i], 0, bufferSize, 0,
                &vulkan_context_->uniform_buffers_mapped[i]);
  }
}

}  // namespace nextgen::engine::rendering::vulkan
