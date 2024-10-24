#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_SYNC_OBJECT_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_SYNC_OBJECT_H

#include "components/rendering/api/vulkan/vulkan_context.h"

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes)
namespace nextgen::engine::rendering::vulkan {

struct VulkanSyncObject {
  VulkanContext* vulkan_context_{};

  VulkanSyncObject();

  void Initialize(VulkanContext& vulkan_context);
  void Shutdown() const noexcept;

  ~VulkanSyncObject();

  // copy
  VulkanSyncObject& operator=(const VulkanSyncObject&) = delete;
  VulkanSyncObject(const VulkanSyncObject&) = delete;
  // move
  VulkanSyncObject& operator=(VulkanSyncObject&&) = default;
  VulkanSyncObject(VulkanSyncObject&&) = default;

 private:
  void CreateSyncObjects() const;
};

}  // namespace nextgen::engine::rendering::vulkan
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes)

#endif