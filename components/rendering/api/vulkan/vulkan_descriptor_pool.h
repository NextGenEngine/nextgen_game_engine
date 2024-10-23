#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_DESCRIPTOR_POOL_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_DESCRIPTOR_POOL_H

#include "components/rendering/api/vulkan/vulkan_context.h"

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes)
namespace nextgen::engine::rendering::vulkan {

struct VulkanDescriptorPool {
  VulkanContext* vulkan_context_{};

  VulkanDescriptorPool();

  void Initialize(VulkanContext& vulkan_context);
  void Shutdown() const noexcept;

  ~VulkanDescriptorPool();

  // copy
  VulkanDescriptorPool& operator=(const VulkanDescriptorPool&) = delete;
  VulkanDescriptorPool(const VulkanDescriptorPool&) = delete;
  // move
  VulkanDescriptorPool& operator=(VulkanDescriptorPool&&) = default;
  VulkanDescriptorPool(VulkanDescriptorPool&&) = default;

 private:
  void CreateDescriptorPool() const;
};

}  // namespace nextgen::engine::rendering::vulkan
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes)

#endif
