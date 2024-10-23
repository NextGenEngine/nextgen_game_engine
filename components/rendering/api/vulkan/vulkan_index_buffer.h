#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_INDEX_BUFFER_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_INDEX_BUFFER_H

#include "components/rendering/api/vulkan/vulkan_buffer.h"
#include "components/rendering/api/vulkan/vulkan_context.h"

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes)
namespace nextgen::engine::rendering::vulkan {

struct VulkanIndexBuffer {
  VulkanContext* vulkan_context_{};
  VulkanBuffer* vulkan_buffer_{};

  VulkanIndexBuffer();

  void Initialize(VulkanContext& vulkan_context, VulkanBuffer& vulkan_buffer);
  void Shutdown() const noexcept;

  void CreateIndexBuffer() const;

  ~VulkanIndexBuffer();

  // copy
  VulkanIndexBuffer& operator=(const VulkanIndexBuffer&) = delete;
  VulkanIndexBuffer(const VulkanIndexBuffer&) = delete;
  // move
  VulkanIndexBuffer& operator=(VulkanIndexBuffer&&) = default;
  VulkanIndexBuffer(VulkanIndexBuffer&&) = default;

 private:
};

}  // namespace nextgen::engine::rendering::vulkan
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes)

#endif
