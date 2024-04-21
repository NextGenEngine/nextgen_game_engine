#include "components/rendering/api/vulkan/config_strategy/vulkan_config_strategy_default.h"

#include "components/configuration/config_manager.h"
#include "components/rendering/api/vulkan/config_strategy/vulkan_config_validator.h"
#include "components/rendering/api/vulkan/vulkan_config.h"

namespace nextgen::engine::rendering::vulkan {

using configuration::ComponentConfig;

bool VulkanConfigurationDefaultStrategy::Configure() {
  VulkanConfig const config =
      vulkan_rendering_api_->vulkan_instance_.GetDefaultConfiguration();

  if (!VulkanConfigValidator::Validate(config)) {
    return false;
  }

  component_config_->UpdateConfig(config);
  component_config_->SaveConfig();
  vulkan_rendering_api_->ApplyConfiguration(&config);

  return true;
}

void VulkanConfigurationDefaultStrategy::Initialize(
    ComponentConfig& component_config,
    VulkanRenderingApi& vulkan_rendering_api) {
  vulkan_rendering_api_ = &vulkan_rendering_api;
  component_config_ = &component_config;
}

}  // namespace nextgen::engine::rendering::vulkan
