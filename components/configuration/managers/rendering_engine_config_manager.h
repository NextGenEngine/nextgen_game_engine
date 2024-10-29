#ifndef NEXTGEN_ENGINE_CONFIGURATION_MANAGERS_RENDERING_ENGINE_CONFIG_MANAGER_H
#define NEXTGEN_ENGINE_CONFIGURATION_MANAGERS_RENDERING_ENGINE_CONFIG_MANAGER_H

#include "components/rendering/rendering_config.h"
#include "components/rendering/rendering_engine.h"
#include "config_manager_template.h"

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes)

namespace nextgen::engine::configuration::managers {

using RenderingEngineConfigManagerBase =
    ConfigComponentManager<rendering::RenderingEngine,
                           rendering::RenderingEngineConfig>;

struct RenderingEngineConfigManager : public RenderingEngineConfigManagerBase {
  explicit RenderingEngineConfigManager(
      rendering::RenderingEngine& renderingEngine,
      ConfigWithDefaultFlag<rendering::RenderingEngineConfig> config)
      : RenderingEngineConfigManagerBase(renderingEngine, config) {}
};

}  // namespace nextgen::engine::configuration::managers
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes)

#endif
