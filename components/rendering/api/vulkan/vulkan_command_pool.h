#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_COMMAND_POOL_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_COMMAND_POOL_H

#include <vulkan/vulkan_core.h>

#include "components/rendering/api/vulkan/vulkan_device.hh"
#include "vulkan_context.h"

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)
namespace nextgen::engine::rendering::vulkan {

struct VulkanCommandPool {
  VulkanContext& vulkan_context_;
  VulkanDevice& vulkan_device_;

  explicit VulkanCommandPool(VulkanContext& vulkan_context,
                             VulkanDevice& vulkan_device);

  void Initialize();
  void Shutdown() const noexcept;

  ~VulkanCommandPool();

  // copy
  VulkanCommandPool& operator=(const VulkanCommandPool&) = delete;
  VulkanCommandPool(const VulkanCommandPool&) = delete;
  // move
  VulkanCommandPool& operator=(VulkanCommandPool&&) = delete;
  VulkanCommandPool(VulkanCommandPool&&) = default;

 private:
  void CreateCommandPool() const;
};
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)

}  // namespace nextgen::engine::rendering::vulkan

#endif
