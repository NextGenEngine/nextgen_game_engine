#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_UNIFORM_BUFFER_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_UNIFORM_BUFFER_H

#include "components/rendering/api/vulkan/vulkan_buffer.h"
#include "components/rendering/api/vulkan/vulkan_context.h"

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes)
namespace nextgen::engine::rendering::vulkan {

struct VulkanUniformBuffer {
  VulkanContext* vulkan_context_{};
  VulkanBuffer* vulkan_buffer_{};

  VulkanUniformBuffer();

  void Initialize(VulkanContext& vulkan_context, VulkanBuffer& vulkan_buffer);
  void Shutdown() const noexcept;

  void CreateUniformBuffers() const;

  ~VulkanUniformBuffer();

  // copy
  VulkanUniformBuffer& operator=(const VulkanUniformBuffer&) = delete;
  VulkanUniformBuffer(const VulkanUniformBuffer&) = delete;
  // move
  VulkanUniformBuffer& operator=(VulkanUniformBuffer&&) = default;
  VulkanUniformBuffer(VulkanUniformBuffer&&) = default;

  struct UniformBufferObject {
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view;
    alignas(16) glm::mat4 proj;
  };

 private:
};

}  // namespace nextgen::engine::rendering::vulkan
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes)

#endif
