#include "vulkan_config_strategy.h"

#include "components/rendering/vulkan/vulkan_config.h"
#include "components/rendering/vulkan/vulkan_instance.h"
#include "components/rendering/vulkan/vulkan_rendering.h"

namespace nextgen::engine::rendering::vulkan {

void VulkanDefaultConfigStrategy::Configure() {
  VulkanConfig const config =
      vulkan_rendering_api_->vulkan_instance_.GetDefaultConfiguration();
  vulkan_rendering_api_->set_config(config);
  component_config_.UpdateConfig(config);
  component_config_.SaveConfig();  // Save configuration after applying
}

}  // namespace nextgen::engine::rendering::vulkan
