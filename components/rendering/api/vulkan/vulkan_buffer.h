#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_BUFFER_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_BUFFER_H

#include <vulkan/vulkan_core.h>

#include "components/rendering/api/vulkan/vulkan_context.h"

namespace nextgen::engine::rendering::vulkan {

struct VulkanBuffer {
  VulkanContext* vulkan_context_;

  void Initialize(VulkanContext& vulkan_context);

  void createVertexBuffer(VkDevice device, VkPhysicalDevice physicalDevice);
};

}  // namespace nextgen::engine::rendering::vulkan

#endif
