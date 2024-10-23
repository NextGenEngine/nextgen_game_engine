#include "components/rendering/api/vulkan/vulkan_command_pool.h"

#include <vulkan/vulkan_core.h>

#include <iostream>
#include <stdexcept>
#include <vector>

#include "components/rendering/api/vulkan/vulkan_context.h"
#include "components/rendering/api/vulkan/vulkan_device.hh"

namespace nextgen::engine::rendering::vulkan {

VulkanCommandPool::VulkanCommandPool() {
  std::cout << "VulkanCommandPool object instantiated\n";
}

VulkanCommandPool::~VulkanCommandPool() {
  std::cout << "VulkanCommandPool instance destroyed\n";
}

void VulkanCommandPool::Initialize(VulkanContext& vulkan_context,
                                   VulkanDevice& vulkan_device) {
  vulkan_context_ = &vulkan_context;
  vulkan_device_ = &vulkan_device;

  CreateCommandPool();
}

void VulkanCommandPool::Shutdown() const noexcept {
  if (vulkan_context_ == nullptr || vulkan_context_->device == nullptr) {
    std::cout << "VulkanCommandPool: Vulkan context or device is null; no need "
                 "to cleanup command pool\n";
    std::cout << "VulkanCommandPool: shutdown complete\n";
    return;
  }

  if (vulkan_context_->command_pool != VK_NULL_HANDLE) {
    vkDestroyCommandPool(vulkan_context_->device, vulkan_context_->command_pool,
                         nullptr);
    vulkan_context_->command_pool = VK_NULL_HANDLE;
    std::cout << "VulkanCommandPool: command_pool destroyed\n";
  } else {
    std::cout << "VulkanCommandPool: command_pool is null; no "
                 "need to destroy it\n";
  }

  std::cout << "VulkanCommandPool: shutdown complete\n";
}

void VulkanCommandPool::CreateCommandPool() const {
  QueueFamilyIndices queueFamilyIndices =
      vulkan_device_->findQueueFamilies(vulkan_context_->physical_device);

  if (!queueFamilyIndices.graphicsFamily.has_value()) {
    throw std::runtime_error(
        "queueFamilyIndices is empty. failed to create graphics command pool!");
  }

  VkCommandPoolCreateInfo poolInfo{};
  poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
  poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

  if (vkCreateCommandPool(vulkan_context_->device, &poolInfo, nullptr,
                          &vulkan_context_->command_pool) != VK_SUCCESS) {
    throw std::runtime_error("failed to create graphics command pool!");
  }
}

}  // namespace nextgen::engine::rendering::vulkan
