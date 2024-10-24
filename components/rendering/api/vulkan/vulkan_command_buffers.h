#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_COMMAND_BUFFERS_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_COMMAND_BUFFERS_H

#include "components/rendering/api/vulkan/vulkan_context.h"

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)
namespace nextgen::engine::rendering::vulkan {

struct VulkanCommandBuffers {
  VulkanContext& vulkan_context_;

  explicit VulkanCommandBuffers(VulkanContext& vulkan_context);

  void Initialize() const;
  static void Shutdown() noexcept;

  VkCommandBuffer BeginSingleTimeCommands() const;
  void EndSingleTimeCommands(VkCommandBuffer commandBuffer) const;

  ~VulkanCommandBuffers();

  // copy
  VulkanCommandBuffers& operator=(const VulkanCommandBuffers&) = delete;
  VulkanCommandBuffers(const VulkanCommandBuffers&) = delete;
  // move
  VulkanCommandBuffers& operator=(VulkanCommandBuffers&&) = delete;
  VulkanCommandBuffers(VulkanCommandBuffers&&) = default;

 private:
  void CreateCommandBuffers() const;
};

}  // namespace nextgen::engine::rendering::vulkan
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)

#endif
