#ifndef NEXTGEN_ENGINE_CONFIGURATION_CONFIG_ORCHESTRATOR_H
#define NEXTGEN_ENGINE_CONFIGURATION_CONFIG_ORCHESTRATOR_H

#include "components/configuration/managers/rendering_engine_config_manager.h"
#include "components/configuration/managers/vulkan_rendering_api_config_manager.h"
#include "components/configuration/repository/config_repo.h"
#include "components/rendering/api/vulkan/vulkan_rendering.h"
#include "components/rendering/rendering_engine.h"

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes)

namespace nextgen::engine::configuration {

using rendering::RenderingEngine;
using rendering::vulkan::VulkanRenderingApi;

struct ConfigOrchestrator {
  explicit ConfigOrchestrator(ConfigRepository& config_repo,
                              RenderingEngine& rendering_engine,
                              VulkanRenderingApi& vulkan_rendering_api);
  void Configure();

  managers::RenderingEngineConfigManager rendering_config_manager_;
  managers::VulkanRenderingApiConfigManager vulkan_config_manager_;
};

}  // namespace nextgen::engine::configuration
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes)

#endif
