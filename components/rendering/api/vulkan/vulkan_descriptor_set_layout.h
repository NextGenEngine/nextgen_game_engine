#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_DESCRIPTOR_SET_LAYOUT_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_DESCRIPTOR_SET_LAYOUT_H

#include "components/rendering/api/vulkan/vulkan_context.h"

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes)
namespace nextgen::engine::rendering::vulkan {

struct VulkanDescriptorSetLayout {
  VulkanContext* vulkan_context_{};

  VulkanDescriptorSetLayout();

  void Initialize(VulkanContext& vulkan_context);
  void Shutdown() const noexcept;

  ~VulkanDescriptorSetLayout();

  // copy
  VulkanDescriptorSetLayout& operator=(const VulkanDescriptorSetLayout&) =
      delete;
  VulkanDescriptorSetLayout(const VulkanDescriptorSetLayout&) = delete;
  // move
  VulkanDescriptorSetLayout& operator=(VulkanDescriptorSetLayout&&) = default;
  VulkanDescriptorSetLayout(VulkanDescriptorSetLayout&&) = default;

 private:
  void CreateDescriptorSetLayout() const;
};

}  // namespace nextgen::engine::rendering::vulkan
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes)

#endif
