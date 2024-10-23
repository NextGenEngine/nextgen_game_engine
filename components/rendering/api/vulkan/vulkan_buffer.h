#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_BUFFER_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_BUFFER_H

#include "components/rendering/api/vulkan/vulkan_command_buffers.h"
#include "components/rendering/api/vulkan/vulkan_context.h"
#include "components/rendering/api/vulkan/vulkan_device.hh"

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes)
namespace nextgen::engine::rendering::vulkan {

struct VulkanBuffer {
  VulkanContext* vulkan_context_{};
  VulkanDevice* vulkan_device_{};
  VulkanCommandBuffers* vulkan_command_buffers_{};

  struct BufferUsage {
    VkBufferUsageFlags flags;
  };
  struct MemoryProperty {
    VkMemoryPropertyFlags flags;
  };

  VulkanBuffer();

  void Initialize(VulkanContext& vulkan_context, VulkanDevice& vulkan_device,
                  VulkanCommandBuffers& vulkan_command_buffers);
  static void Shutdown() noexcept;

  void CreateBuffer(VkDeviceSize size, BufferUsage buffer_usage,
                    MemoryProperty memory_properties, VkBuffer& buffer,
                    VkDeviceMemory& bufferMemory) const;
  void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer,
                  VkDeviceSize size) const;

  ~VulkanBuffer();

  // copy
  VulkanBuffer& operator=(const VulkanBuffer&) = delete;
  VulkanBuffer(const VulkanBuffer&) = delete;
  // move
  VulkanBuffer& operator=(VulkanBuffer&&) = default;
  VulkanBuffer(VulkanBuffer&&) = default;

 private:
};

}  // namespace nextgen::engine::rendering::vulkan
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes)

#endif
