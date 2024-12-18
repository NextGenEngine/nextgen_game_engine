#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_SWAPCHAIN_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_SWAPCHAIN_H

#include "components/rendering/api/vulkan/vulkan_context.h"
#include "components/rendering/api/vulkan/vulkan_device.hh"
#include "components/rendering/api/vulkan/vulkan_swapchain_types.h"

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)
namespace nextgen::engine::rendering::vulkan {

struct VulkanSwapChain {
  VulkanContext& vulkan_context_;
  VulkanDevice& vulkan_device_;

  explicit VulkanSwapChain(VulkanContext& vulkan_context,
                           VulkanDevice& vulkan_device);

  void Initialize();
  void Shutdown() const noexcept;

  void CreateImageViews() const;

  ~VulkanSwapChain();

  // copy
  VulkanSwapChain& operator=(const VulkanSwapChain&) = delete;
  VulkanSwapChain(const VulkanSwapChain&) = delete;
  // move
  VulkanSwapChain& operator=(VulkanSwapChain&&) = delete;
  VulkanSwapChain(VulkanSwapChain&&) = default;

 private:
  void CreateSwapChain();
  SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device) const;
  static VkSurfaceFormatKHR chooseSwapSurfaceFormat(
      const std::vector<VkSurfaceFormatKHR>& availableFormats);
  static VkPresentModeKHR chooseSwapPresentMode(
      const std::vector<VkPresentModeKHR>& availablePresentModes);
  VkExtent2D chooseSwapExtent(
      const VkSurfaceCapabilitiesKHR& capabilities) const;
};

}  // namespace nextgen::engine::rendering::vulkan
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)

#endif
