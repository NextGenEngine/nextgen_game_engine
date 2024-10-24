#include "components/rendering/api/vulkan/vulkan_command_buffers.h"

#include <vulkan/vulkan_core.h>

#include <cstdint>
#include <iostream>
#include <stdexcept>

#include "components/rendering/api/vulkan/vulkan_constants.h"
#include "components/rendering/api/vulkan/vulkan_context.h"

namespace nextgen::engine::rendering::vulkan {

VulkanCommandBuffers::VulkanCommandBuffers(VulkanContext& vulkan_context)
    : vulkan_context_(vulkan_context) {
  std::cout << "VulkanCommandBuffers object instantiated\n";
}

VulkanCommandBuffers::~VulkanCommandBuffers() {
  std::cout << "VulkanCommandBuffers instance destroyed\n";
}

void VulkanCommandBuffers::Initialize() const { CreateCommandBuffers(); }

void VulkanCommandBuffers::Shutdown() noexcept {
  std::cout << "VulkanCommandBuffers: shutdown complete\n";
}

VkCommandBuffer VulkanCommandBuffers::BeginSingleTimeCommands() const {
  VkCommandBufferAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocInfo.commandPool = vulkan_context_.command_pool;
  allocInfo.commandBufferCount = 1;

  VkCommandBuffer commandBuffer{};
  vkAllocateCommandBuffers(vulkan_context_.device, &allocInfo, &commandBuffer);

  VkCommandBufferBeginInfo beginInfo{};
  beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

  vkBeginCommandBuffer(commandBuffer, &beginInfo);

  return commandBuffer;
}

void VulkanCommandBuffers::EndSingleTimeCommands(
    VkCommandBuffer commandBuffer) const {
  vkEndCommandBuffer(commandBuffer);

  VkSubmitInfo submitInfo{};
  submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submitInfo.commandBufferCount = 1;
  submitInfo.pCommandBuffers = &commandBuffer;

  vkQueueSubmit(vulkan_context_.graphics_queue, 1, &submitInfo, VK_NULL_HANDLE);
  vkQueueWaitIdle(vulkan_context_.graphics_queue);

  vkFreeCommandBuffers(vulkan_context_.device, vulkan_context_.command_pool, 1,
                       &commandBuffer);
}

void VulkanCommandBuffers::CreateCommandBuffers() const {
  vulkan_context_.command_buffers.resize(MAX_FRAMES_IN_FLIGHT);

  VkCommandBufferAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocInfo.commandPool = vulkan_context_.command_pool;
  allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocInfo.commandBufferCount =
      static_cast<uint32_t>(vulkan_context_.command_buffers.size());

  if (vkAllocateCommandBuffers(vulkan_context_.device, &allocInfo,
                               vulkan_context_.command_buffers.data()) !=
      VK_SUCCESS) {
    throw std::runtime_error("failed to allocate command buffers!");
  }
}

}  // namespace nextgen::engine::rendering::vulkan
