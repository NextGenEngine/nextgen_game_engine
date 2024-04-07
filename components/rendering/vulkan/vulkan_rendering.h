#ifndef NEXTGEN_ENGINE_VULKAN_RENDERING_H
#define NEXTGEN_ENGINE_VULKAN_RENDERING_H

#include <vulkan/vulkan_core.h>
#include <yaml-cpp/exceptions.h>

#include "components/configuration/config_manager.h"
#include "vulkan_config.h"
#include "vulkan_operations.h"

namespace rendering {

struct VulkanRenderer {
  static void init(const ComponentConfig &componentConfig);

  static void render();
};

}  // namespace rendering

VulkanConfig GetDefaultConfig();

#endif
