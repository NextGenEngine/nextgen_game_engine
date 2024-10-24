#include "components/rendering/api/vulkan/vulkan_buffer.h"

#include <vulkan/vulkan_core.h>

#include <cstddef>
#include <iostream>
#include <stdexcept>

#include "components/rendering/api/vulkan/vulkan_command_buffers.h"
#include "components/rendering/api/vulkan/vulkan_context.h"
#include "components/rendering/api/vulkan/vulkan_device.hh"

namespace nextgen::engine::rendering::vulkan {

VulkanBuffer::VulkanBuffer(VulkanContext& vulkan_context,
                           VulkanDevice& vulkan_device,
                           VulkanCommandBuffers& vulkan_command_buffers)
    : vulkan_context_(vulkan_context),
      vulkan_device_(vulkan_device),
      vulkan_command_buffers_(vulkan_command_buffers) {
  std::cout << "VulkanBuffer object instantiated\n";
}

VulkanBuffer::~VulkanBuffer() {
  std::cout << "VulkanBuffer instance destroyed\n";
}

void VulkanBuffer::Initialize() {}

void VulkanBuffer::Shutdown() noexcept {
  std::cout << "VulkanBuffer: shutdown complete\n";
}

void VulkanBuffer::CreateBuffer(VkDeviceSize size, BufferUsage buffer_usage,
                                MemoryProperty memory_properties,
                                VkBuffer& buffer,
                                VkDeviceMemory& bufferMemory) const {
  VkBufferCreateInfo bufferInfo{};
  bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  bufferInfo.size = size;
  bufferInfo.usage = buffer_usage.flags;
  bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

  if (vkCreateBuffer(vulkan_context_.device, &bufferInfo, nullptr, &buffer) !=
      VK_SUCCESS) {
    throw std::runtime_error("failed to create buffer!");
  }

  VkMemoryRequirements memRequirements;
  vkGetBufferMemoryRequirements(vulkan_context_.device, buffer,
                                &memRequirements);

  VkMemoryAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  allocInfo.allocationSize = memRequirements.size;
  allocInfo.memoryTypeIndex = vulkan_device_.FindMemoryType(
      memRequirements.memoryTypeBits, memory_properties.flags);

  if (vkAllocateMemory(vulkan_context_.device, &allocInfo, nullptr,
                       &bufferMemory) != VK_SUCCESS) {
    throw std::runtime_error("failed to allocate buffer memory!");
  }

  vkBindBufferMemory(vulkan_context_.device, buffer, bufferMemory, 0);
}

void VulkanBuffer::CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer,
                              VkDeviceSize size) const {
  VkCommandBuffer commandBuffer =
      vulkan_command_buffers_.BeginSingleTimeCommands();

  VkBufferCopy copyRegion{};
  copyRegion.size = size;
  vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

  vulkan_command_buffers_.EndSingleTimeCommands(commandBuffer);
}

}  // namespace nextgen::engine::rendering::vulkan
