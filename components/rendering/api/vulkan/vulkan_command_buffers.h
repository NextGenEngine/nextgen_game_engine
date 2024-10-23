#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_COMMAND_BUFFERS_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_COMMAND_BUFFERS_H

#include "components/rendering/api/vulkan/vulkan_context.h"

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes)
namespace nextgen::engine::rendering::vulkan {

struct VulkanCommandBuffers {
  VulkanContext* vulkan_context_{};

  VulkanCommandBuffers();

  void Initialize(VulkanContext& vulkan_context);
  static void Shutdown() noexcept;
  void CreateCommandBuffers() const;

  VkCommandBuffer BeginSingleTimeCommands() const;
  void EndSingleTimeCommands(VkCommandBuffer commandBuffer) const;

  ~VulkanCommandBuffers();

  // copy
  VulkanCommandBuffers& operator=(const VulkanCommandBuffers&) = delete;
  VulkanCommandBuffers(const VulkanCommandBuffers&) = delete;
  // move
  VulkanCommandBuffers& operator=(VulkanCommandBuffers&&) = default;
  VulkanCommandBuffers(VulkanCommandBuffers&&) = default;

 private:
};

}  // namespace nextgen::engine::rendering::vulkan
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes)

#endif
