#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_DESCRIPTOR_SET_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_DESCRIPTOR_SET_H

#include "components/rendering/api/vulkan/vulkan_context.h"

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes)
namespace nextgen::engine::rendering::vulkan {

struct VulkanDescriptorSet {
  VulkanContext* vulkan_context_{};

  VulkanDescriptorSet();

  void Initialize(VulkanContext& vulkan_context);
  void Shutdown() const noexcept;

  ~VulkanDescriptorSet();

  // copy
  VulkanDescriptorSet& operator=(const VulkanDescriptorSet&) = delete;
  VulkanDescriptorSet(const VulkanDescriptorSet&) = delete;
  // move
  VulkanDescriptorSet& operator=(VulkanDescriptorSet&&) = default;
  VulkanDescriptorSet(VulkanDescriptorSet&&) = default;

 private:
  void CreateDescriptorSets() const;
};

}  // namespace nextgen::engine::rendering::vulkan
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes)

#endif