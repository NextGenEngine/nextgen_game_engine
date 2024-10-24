#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_UNIFORM_BUFFER_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_UNIFORM_BUFFER_H

#include "components/rendering/api/vulkan/vulkan_buffer.h"
#include "components/rendering/api/vulkan/vulkan_context.h"

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)
namespace nextgen::engine::rendering::vulkan {

struct VulkanUniformBuffer {
  VulkanContext& vulkan_context_;
  VulkanBuffer& vulkan_buffer_;

  explicit VulkanUniformBuffer(VulkanContext& vulkan_context,
                               VulkanBuffer& vulkan_buffer);

  void Initialize() const;
  void Shutdown() const noexcept;

  void CreateUniformBuffers() const;

  ~VulkanUniformBuffer();

  // copy
  VulkanUniformBuffer& operator=(const VulkanUniformBuffer&) = delete;
  VulkanUniformBuffer(const VulkanUniformBuffer&) = delete;
  // move
  VulkanUniformBuffer& operator=(VulkanUniformBuffer&&) = delete;
  VulkanUniformBuffer(VulkanUniformBuffer&&) = default;

  struct UniformBufferObject {
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view;
    alignas(16) glm::mat4 proj;
  };

 private:
};

}  // namespace nextgen::engine::rendering::vulkan
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)

#endif
