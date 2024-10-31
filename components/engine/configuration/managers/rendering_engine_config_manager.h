#ifndef NEXTGEN_ENGINE_CONFIGURATION_MANAGERS_RENDERING_ENGINE_CONFIG_MANAGER_H
#define NEXTGEN_ENGINE_CONFIGURATION_MANAGERS_RENDERING_ENGINE_CONFIG_MANAGER_H

#include "components/configuration/managers/config_manager_template.h"
#include "components/rendering/rendering_engine.h"

namespace nextgen::engine::configuration::managers {

using RenderingEngineConfigManager =
    ConfigComponentManager<rendering::RenderingEngine>;

}  // namespace nextgen::engine::configuration::managers

#endif
