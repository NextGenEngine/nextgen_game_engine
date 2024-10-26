#include "components/rendering/api/vulkan/config_strategy/vulkan_config_strategy_primary.h"

#include "components/rendering/api/vulkan/config_strategy/vulkan_config_validator.h"
#include "components/rendering/api/vulkan/vulkan_config.h"
#include "components/rendering/api/vulkan/vulkan_rendering.h"

namespace nextgen::engine::rendering::vulkan {

VulkanConfigurationPrimaryStrategy::VulkanConfigurationPrimaryStrategy(
    ComponentConfig& component_config, VulkanRenderingApi& vulkan_rendering_api)
    : VulkanConfigurationPrimaryStrategyData(component_config,
                                             vulkan_rendering_api) {}

bool VulkanConfigurationPrimaryStrategy::Configure() {
  auto vulkan_config = component_config_.LoadConfig<VulkanConfig>();

  if (!vulkan_config) {
    return false;
  }

  if (!VulkanConfigValidator::Validate(*vulkan_config)) {
    return false;
  }

  vulkan_rendering_api_.ApplyConfiguration(&*vulkan_config);

  return true;
}

}  // namespace nextgen::engine::rendering::vulkan
