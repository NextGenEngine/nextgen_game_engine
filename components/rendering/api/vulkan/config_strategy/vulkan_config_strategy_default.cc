#include "components/rendering/api/vulkan/config_strategy/vulkan_config_strategy_default.h"

#include "components/rendering/api/vulkan/config_strategy/vulkan_config_validator.h"
#include "components/rendering/api/vulkan/vulkan_config.h"
#include "components/rendering/api/vulkan/vulkan_rendering.h"

namespace nextgen::engine::rendering::vulkan {

VulkanConfigurationDefaultStrategy::VulkanConfigurationDefaultStrategy(
    ComponentConfig& component_config, VulkanRenderingApi& vulkan_rendering_api)
    : VulkanConfigurationDefaultStrategyData(component_config,
                                             vulkan_rendering_api) {}

bool VulkanConfigurationDefaultStrategy::Configure() {
  VulkanConfig const config =
      vulkan_rendering_api_.vulkan_instance_.GetDefaultConfiguration();

  if (!VulkanConfigValidator::Validate(config)) {
    return false;
  }

  component_config_.UpdateConfig(config);
  component_config_.Save();
  vulkan_rendering_api_.ApplyConfiguration(config);

  return true;
}

}  // namespace nextgen::engine::rendering::vulkan
