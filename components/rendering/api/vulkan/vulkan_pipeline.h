#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_PIPELINE_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_PIPELINE_H

#include <vulkan/vulkan_core.h>

#include "components/rendering/api/vulkan/vulkan_context.h"

namespace nextgen::engine::rendering::vulkan {

struct GraphicsPipeline {
  VulkanContext* vulkan_context_;

  void Initialize(VulkanContext& vulkan_context);

  void createGraphicsPipeline(VkDevice device);
};

}  // namespace nextgen::engine::rendering::vulkan

#endif
