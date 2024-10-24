#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_PIPELINE_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_PIPELINE_H

#include <vulkan/vulkan_core.h>

#include "components/rendering/api/vulkan/vulkan_context.h"

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)
namespace nextgen::engine::rendering::vulkan {

struct VulkanGraphicsPipeline {
  VulkanContext& vulkan_context_;

  explicit VulkanGraphicsPipeline(VulkanContext& vulkan_context);

  void Initialize();
  void Shutdown() const noexcept;

  ~VulkanGraphicsPipeline();

  // copy
  VulkanGraphicsPipeline& operator=(const VulkanGraphicsPipeline&) = delete;
  VulkanGraphicsPipeline(const VulkanGraphicsPipeline&) = delete;
  // move
  VulkanGraphicsPipeline& operator=(VulkanGraphicsPipeline&&) = delete;
  VulkanGraphicsPipeline(VulkanGraphicsPipeline&&) = default;

 private:
  void CreateGraphicsPipeline();
  VkShaderModule CreateShaderModule(const std::vector<char>& code) const;
};

}  // namespace nextgen::engine::rendering::vulkan
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)

#endif
