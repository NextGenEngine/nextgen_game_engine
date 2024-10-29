#ifndef NEXTGEN_ENGINE_CONFIGURATION_CONFIG_ORCHESTRATOR_H
#define NEXTGEN_ENGINE_CONFIGURATION_CONFIG_ORCHESTRATOR_H

#include "components/configuration/managers/rendering_engine_config_manager.h"
#include "components/configuration/managers/vulkan_rendering_api_config_manager.h"
#include "components/configuration/repository/config_repo.h"
#include "components/rendering/rendering_engine.h"

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes)

namespace nextgen::engine::configuration {

struct ConfigOrchestrator {
  explicit ConfigOrchestrator(ConfigRepository& config_manager,
                              rendering::RenderingEngine& rendering_engine);
  void Configure();

  managers::RenderingEngineConfigManager rendering_config_manager_;
  managers::VulkanRenderingApiConfigManager vulkan_config_manager_;
};

}  // namespace nextgen::engine::configuration
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes)

#endif
