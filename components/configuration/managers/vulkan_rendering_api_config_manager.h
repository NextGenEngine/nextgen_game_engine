#ifndef NEXTGEN_ENGINE_CONFIGURATION_MANAGERS_VULKAN_RENDERING_API_CONFIG_MANAGER_H
#define NEXTGEN_ENGINE_CONFIGURATION_MANAGERS_VULKAN_RENDERING_API_CONFIG_MANAGER_H

#include "components/rendering/api/vulkan/vulkan_config.h"
#include "components/rendering/api/vulkan/vulkan_rendering.h"
#include "config_manager_template.h"

namespace nextgen::engine::configuration::managers {

using VulkanRenderingApiConfigManager =
    ConfigComponentManager<rendering::vulkan::VulkanRenderingApi,
                           rendering::vulkan::VulkanConfig>;

}  // namespace nextgen::engine::configuration::managers

#endif
