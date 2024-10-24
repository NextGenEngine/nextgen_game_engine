#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_DESCRIPTOR_POOL_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_DESCRIPTOR_POOL_H

#include "components/rendering/api/vulkan/vulkan_context.h"

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)
namespace nextgen::engine::rendering::vulkan {

struct VulkanDescriptorPool {
  VulkanContext& vulkan_context_;

  explicit VulkanDescriptorPool(VulkanContext& vulkan_context);

  void Initialize();
  void Shutdown() const noexcept;

  ~VulkanDescriptorPool();

  // copy
  VulkanDescriptorPool& operator=(const VulkanDescriptorPool&) = delete;
  VulkanDescriptorPool(const VulkanDescriptorPool&) = delete;
  // move
  VulkanDescriptorPool& operator=(VulkanDescriptorPool&&) = delete;
  VulkanDescriptorPool(VulkanDescriptorPool&&) = default;

 private:
  void CreateDescriptorPool() const;
};

}  // namespace nextgen::engine::rendering::vulkan
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)

#endif
