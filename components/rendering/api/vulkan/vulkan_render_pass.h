#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_RENDER_PASS_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_RENDER_PASS_H

#include <vulkan/vulkan_core.h>

#include "components/rendering/api/vulkan/vulkan_context.h"

namespace nextgen::engine::rendering::vulkan {

struct VulkanRenderPass {
  VulkanContext* vulkan_context_;

  void Initialize(VulkanContext& vulkan_context);

  void createRenderPass(VkDevice device, VkFormat swapChainImageFormat);
};

}  // namespace nextgen::engine::rendering::vulkan

#endif
