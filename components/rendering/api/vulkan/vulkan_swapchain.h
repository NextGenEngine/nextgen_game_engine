#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_SWAPCHAIN_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_SWAPCHAIN_H

#include <iostream>

#include "components/rendering/api/vulkan/vulkan_context.h"
namespace nextgen::engine::rendering::vulkan {

struct VulkanSwapChain {
  VulkanContext* vulkan_context_{};

  VulkanSwapChain() { std::cout << "VulkanSwapChain object created\n"; }

  void Initialize(VulkanContext& vulkan_context);

  void CreateSwapChain() const;
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
