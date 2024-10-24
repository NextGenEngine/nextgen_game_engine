#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_DEVICE_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_DEVICE_H

#include "components/rendering/api/vulkan/vulkan_config.h"
#include "components/rendering/api/vulkan/vulkan_swapchain_types.h"
#include "vulkan_context.h"

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)
namespace nextgen::engine::rendering::vulkan {

using nextgen::engine::rendering::vulkan::VulkanContext;

struct QueueFamilyIndices {
  std::optional<uint32_t> graphicsFamily;
  std::optional<uint32_t> presentFamily;

  bool isComplete() {
    return graphicsFamily.has_value() && presentFamily.has_value();
  }
};

struct VulkanDevice {
  VulkanConfig& m_vulkan_config;
  VulkanContext& m_vulkan_context;

  explicit VulkanDevice(VulkanConfig& vulkan_config,
                        VulkanContext& vulkan_context);
  void Initialize();
  void Shutdown() const noexcept;

  QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) const;
  VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates,
                               VkImageTiling tiling,
                               VkFormatFeatureFlags features) const;
  VkFormat findDepthFormat() const;
  uint32_t FindMemoryType(uint32_t typeFilter,
                          VkMemoryPropertyFlags properties) const;
  VkImageView CreateImageView(VkImage image, VkFormat format,
                              VkImageAspectFlags aspectFlags) const;

  ~VulkanDevice();

  // copy
  VulkanDevice& operator=(const VulkanDevice&) = delete;
  VulkanDevice(const VulkanDevice&) = delete;
  // move
  VulkanDevice& operator=(VulkanDevice&&) = delete;
  VulkanDevice(VulkanDevice&&) = default;

 private:
  void CreateDevice();
  void pickPhysicalDevice();
  void createLogicalDevice();
  bool isDeviceSuitable(VkPhysicalDevice device);
  bool checkDeviceExtensionSupport(VkPhysicalDevice device);
  SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device) const;
  void DestroyDebugUtilsMessengerEXT(
      const VkAllocationCallbacks* pAllocator) const;

  std::vector<const char*> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
};

}  // namespace nextgen::engine::rendering::vulkan
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)

#endif
