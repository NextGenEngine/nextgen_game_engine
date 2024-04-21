#include "components/rendering/vulkan/config_strategy/vulkan_config_strategy_primary.h"

#include "components/rendering/vulkan/config_strategy/vulkan_config_validator.h"
#include "components/rendering/vulkan/vulkan_config.h"
namespace nextgen::engine::rendering::vulkan {

using configuration::ComponentConfig;

bool VulkanConfigurationPrimaryStrategy::Configure() {
  auto vulkan_config = component_config_.LoadConfig<VulkanConfig>();

  if (!vulkan_config) {
    return false;
  }

  if (!VulkanConfigValidator::Validate(*vulkan_config)) {
    return false;
  }

  vulkan_rendering_api_->ApplyConfiguration(&*vulkan_config);

  return true;
}

void VulkanConfigurationPrimaryStrategy::Initialize(
    ComponentConfig component_config,
    VulkanRenderingApi& vulkan_rendering_api) {
  vulkan_rendering_api_ = &vulkan_rendering_api;
  component_config_ = component_config;
}

}  // namespace nextgen::engine::rendering::vulkan
