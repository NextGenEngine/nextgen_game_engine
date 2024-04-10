#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_SWAPCHAIN_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_SWAPCHAIN_H

#include "components/rendering/vulkan/vulkan_context.h"
namespace nextgen::engine::rendering::vulkan {

class VulkanSwapChain {
  VulkanContext* m_vulkanContext;

 public:
  explicit VulkanSwapChain(VulkanContext* vulkan_context);
  ~VulkanSwapChain();

  // copy
  VulkanSwapChain& operator=(const VulkanSwapChain&) = delete;
  VulkanSwapChain(const VulkanSwapChain&) = delete;
  // move
  VulkanSwapChain& operator=(VulkanSwapChain&&) = default;
  VulkanSwapChain(VulkanSwapChain&&) = default;
};

}  // namespace nextgen::engine::rendering::vulkan

#endif
