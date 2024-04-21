#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_CONFIG_VALIDATOR_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_CONFIG_VALIDATOR_H

#include "components/rendering/api/vulkan/vulkan_config.h"

namespace nextgen::engine::rendering {

struct VulkanConfigValidator {
  static bool Validate(vulkan::VulkanConfig config);
};

}  // namespace nextgen::engine::rendering

#endif
