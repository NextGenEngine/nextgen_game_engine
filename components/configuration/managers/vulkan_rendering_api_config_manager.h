#ifndef NEXTGEN_ENGINE_CONFIGURATION_MANAGERS_VULKAN_RENDERING_API_CONFIG_MANAGER_H
#define NEXTGEN_ENGINE_CONFIGURATION_MANAGERS_VULKAN_RENDERING_API_CONFIG_MANAGER_H

#include "components/rendering/api/vulkan/vulkan_config.h"
#include "components/rendering/api/vulkan/vulkan_rendering.h"
#include "config_manager_template.h"

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes)

namespace nextgen::engine::configuration::managers {

using VulkanRenderingApiConfigManagerBase =
    ConfigComponentManager<rendering::vulkan::VulkanRenderingApi,
                           rendering::vulkan::VulkanConfig>;

struct VulkanRenderingApiConfigManager
    : public VulkanRenderingApiConfigManagerBase {
  explicit VulkanRenderingApiConfigManager(
      rendering::vulkan::VulkanRenderingApi& renderingEngine,
      rendering::vulkan::VulkanConfig config)
      : VulkanRenderingApiConfigManagerBase(renderingEngine, config) {}
};

}  // namespace nextgen::engine::configuration::managers
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes)

#endif
