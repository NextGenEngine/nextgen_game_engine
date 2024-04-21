#include "vulkan_config_strategy.h"

#include "components/rendering/api/vulkan/vulkan_rendering.h"

namespace nextgen::engine::rendering::vulkan {

void VulkanConfigStrategy::Initialize(
    ComponentConfig& component_config,
    VulkanRenderingApi& vulkan_rendering_api) {
  component_config_ = component_config;
  primary_strategy_.Initialize(component_config_, vulkan_rendering_api);
  default_strategy_.Initialize(component_config_, vulkan_rendering_api);
}

}  // namespace nextgen::engine::rendering::vulkan
