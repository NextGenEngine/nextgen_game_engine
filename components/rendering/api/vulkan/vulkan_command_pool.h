#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_COMMAND_POOL_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_COMMAND_POOL_H

#include <vulkan/vulkan_core.h>

#include "components/rendering/api/vulkan/vulkan_device.hh"
#include "vulkan_context.h"

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes)
namespace nextgen::engine::rendering::vulkan {

struct VulkanCommandPool {
  VulkanContext* vulkan_context_{};
  VulkanDevice* vulkan_device_{};

  VulkanCommandPool();

  void Initialize(VulkanContext& vulkan_context, VulkanDevice& vulkan_device);
  void Shutdown() const noexcept;

  ~VulkanCommandPool();

  // copy
  VulkanCommandPool& operator=(const VulkanCommandPool&) = delete;
  VulkanCommandPool(const VulkanCommandPool&) = delete;
  // move
  VulkanCommandPool& operator=(VulkanCommandPool&&) = default;
  VulkanCommandPool(VulkanCommandPool&&) = default;

 private:
  void CreateCommandPool() const;
};
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes)

}  // namespace nextgen::engine::rendering::vulkan

#endif
