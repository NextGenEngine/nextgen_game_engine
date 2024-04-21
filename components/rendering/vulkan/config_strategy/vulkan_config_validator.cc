#include "components/rendering/vulkan/config_strategy/vulkan_config_validator.h"

#include "components/rendering/vulkan/vulkan_config.h"
namespace nextgen::engine::rendering {

bool VulkanConfigValidator::Validate(vulkan::VulkanConfig config) {
  return config.device_id != 0;
}

}  // namespace nextgen::engine::rendering
