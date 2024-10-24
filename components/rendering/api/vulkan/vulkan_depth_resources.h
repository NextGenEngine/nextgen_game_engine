#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_DEPTH_RESOURCES_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_DEPTH_RESOURCES_H

#include "components/rendering/api/vulkan/vulkan_context.h"
#include "components/rendering/api/vulkan/vulkan_device.hh"

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)
namespace nextgen::engine::rendering::vulkan {

struct VulkanDepthResources {
  VulkanContext& vulkan_context_;
  VulkanDevice& vulkan_device_;

  explicit VulkanDepthResources(VulkanContext& vulkan_context,
                                VulkanDevice& vulkan_device);
  void Initialize();
  void Shutdown() const noexcept;

  ~VulkanDepthResources();

  // copy
  VulkanDepthResources& operator=(const VulkanDepthResources&) = delete;
  VulkanDepthResources(const VulkanDepthResources&) = delete;
  // move
  VulkanDepthResources& operator=(VulkanDepthResources&&) = delete;
  VulkanDepthResources(VulkanDepthResources&&) = default;

 private:
  void CreateDepthResources();
  void CreateImage(uint32_t width, uint32_t height, VkFormat format,
                   VkImageTiling tiling, VkImageUsageFlags usage,
                   VkMemoryPropertyFlags properties, VkImage& image,
                   VkDeviceMemory& imageMemory) const;
};

}  // namespace nextgen::engine::rendering::vulkan
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)

#endif
