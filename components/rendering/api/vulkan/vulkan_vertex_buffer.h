#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_VERTEX_BUFFER_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_VERTEX_BUFFER_H

#include "components/rendering/api/vulkan/vulkan_buffer.h"
#include "components/rendering/api/vulkan/vulkan_context.h"

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes)
namespace nextgen::engine::rendering::vulkan {

struct VulkanVertexBuffer {
  VulkanContext* vulkan_context_{};
  VulkanBuffer* vulkan_buffer_{};

  VulkanVertexBuffer();

  void Initialize(VulkanContext& vulkan_context, VulkanBuffer& vulkan_buffer);
  void Shutdown() const noexcept;

  ~VulkanVertexBuffer();

  // copy
  VulkanVertexBuffer& operator=(const VulkanVertexBuffer&) = delete;
  VulkanVertexBuffer(const VulkanVertexBuffer&) = delete;
  // move
  VulkanVertexBuffer& operator=(VulkanVertexBuffer&&) = default;
  VulkanVertexBuffer(VulkanVertexBuffer&&) = default;

 private:
  void CreateVertexBuffer() const;
};

}  // namespace nextgen::engine::rendering::vulkan
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes)

#endif