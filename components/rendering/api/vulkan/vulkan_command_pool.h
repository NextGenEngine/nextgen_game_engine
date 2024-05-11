#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_COMMAND_POOL_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_COMMAND_POOL_H

#include <vulkan/vulkan_core.h>

#include "vulkan_context.h"

namespace nextgen::engine::rendering::vulkan {

struct VulkanCommandPool {
  VulkanContext* vulkan_context_;

  void Initialize(VulkanContext& vulkan_context);

  VkCommandPool createCommandPool(VkDevice device, uint32_t queueFamilyIndex);
  uint32_t findGraphicsQueueFamilyIndex(VkPhysicalDevice physicalDevice);

  void createCommandBuffers(VkDevice device, VkCommandPool commandPool,
                            VkExtent2D swapChainExtent);
};

}  // namespace nextgen::engine::rendering::vulkan

#endif
