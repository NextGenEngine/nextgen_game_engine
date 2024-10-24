#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_FRAME_BUFFERS_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_FRAME_BUFFERS_H

#include <vulkan/vulkan_core.h>

#include "components/rendering/api/vulkan/vulkan_context.h"

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)
namespace nextgen::engine::rendering::vulkan {

struct VulkanFrameBuffers {
  VulkanContext& vulkan_context_;

  explicit VulkanFrameBuffers(VulkanContext& vulkan_context);

  void Initialize();
  void Shutdown() const noexcept;

  ~VulkanFrameBuffers();

  // copy
  VulkanFrameBuffers& operator=(const VulkanFrameBuffers&) = delete;
  VulkanFrameBuffers(const VulkanFrameBuffers&) = delete;
  // move
  VulkanFrameBuffers& operator=(VulkanFrameBuffers&&) = delete;
  VulkanFrameBuffers(VulkanFrameBuffers&&) = default;

 private:
  void CreateFramebuffers() const;
};

}  // namespace nextgen::engine::rendering::vulkan
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)

#endif
