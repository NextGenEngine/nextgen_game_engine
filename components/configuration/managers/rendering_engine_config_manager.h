#ifndef NEXTGEN_ENGINE_CONFIGURATION_MANAGERS_RENDERING_ENGINE_CONFIG_MANAGER_H
#define NEXTGEN_ENGINE_CONFIGURATION_MANAGERS_RENDERING_ENGINE_CONFIG_MANAGER_H

#include "components/rendering/rendering_config.h"
#include "components/rendering/rendering_engine.h"
#include "config_manager_template.h"

namespace nextgen::engine::configuration::managers {

using RenderingEngineConfigManager =
    ConfigComponentManager<rendering::RenderingEngine,
                           rendering::RenderingEngineConfig>;

}  // namespace nextgen::engine::configuration::managers

#endif
