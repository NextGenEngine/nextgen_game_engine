#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_INSTANCE_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_INSTANCE_H

#include "components/rendering/api/vulkan/vulkan_config.h"
#include "components/rendering/api/vulkan/vulkan_context.h"

namespace nextgen::engine::rendering::vulkan {

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)
struct VulkanInstance {
  VulkanContext& vulkan_context_;

  explicit VulkanInstance(VulkanContext& vulkan_context);

  void Initialize();
  void Shutdown() const;

  ~VulkanInstance() = default;

  VulkanConfig GetDefaultConfiguration() const;

  // copy
  VulkanInstance& operator=(const VulkanInstance&) = delete;
  VulkanInstance(const VulkanInstance&) = delete;
  // move
  VulkanInstance& operator=(VulkanInstance&&) = delete;
  VulkanInstance(VulkanInstance&&) = default;

 private:
  void EnumerateAvailableDevices() const;
  static void GetRecommendedResolutionForDevice();
  static const char* GetDeviceTypeName(VkPhysicalDeviceType deviceType);
};
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)

}  // namespace nextgen::engine::rendering::vulkan

#endif
