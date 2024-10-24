#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_RENDER_PASS_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_RENDER_PASS_H

#include <vulkan/vulkan_core.h>

#include "components/rendering/api/vulkan/vulkan_context.h"

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)
namespace nextgen::engine::rendering::vulkan {

struct VulkanRenderPass {
  VulkanContext& vulkan_context_;

  explicit VulkanRenderPass(VulkanContext& vulkan_context);

  void Initialize();
  void Shutdown() const noexcept;

  ~VulkanRenderPass();

  // copy
  VulkanRenderPass& operator=(const VulkanRenderPass&) = delete;
  VulkanRenderPass(const VulkanRenderPass&) = delete;
  // move
  VulkanRenderPass& operator=(VulkanRenderPass&&) = delete;
  VulkanRenderPass(VulkanRenderPass&&) = default;

 private:
  void CreateRenderPass();
  VkFormat findDepthFormat();
  VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates,
                               VkImageTiling tiling,
                               VkFormatFeatureFlags features) const;
};

}  // namespace nextgen::engine::rendering::vulkan
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)

#endif
