#ifndef NEXTGEN_ENGINE_VULKAN_RENDERING_INIT_H
#define NEXTGEN_ENGINE_VULKAN_RENDERING_INIT_H

#include <vulkan/vulkan_core.h>
#include <yaml-cpp/exceptions.h>

#include "components/configuration/config_manager.h"
#include "vulkan_config.h"
#include "vulkan_operations.h"

void LoadVulkanConfig();
VulkanConfig GetDefaultConfig();
void SetComponentConfig(const ComponentConfig& componentConfig);

#endif
