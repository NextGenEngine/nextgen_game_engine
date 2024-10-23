#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_SWAPCHAIN_TYPES_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_SWAPCHAIN_TYPES_H

#include <vulkan/vulkan_core.h>

#include <vector>

namespace nextgen::engine::rendering::vulkan {

struct SwapChainSupportDetails {
  VkSurfaceCapabilitiesKHR capabilities;
  std::vector<VkSurfaceFormatKHR> formats;
  std::vector<VkPresentModeKHR> presentModes;
};

}  // namespace nextgen::engine::rendering::vulkan

#endif
