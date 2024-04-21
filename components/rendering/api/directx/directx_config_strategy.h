#ifndef NEXTGEN_ENGINE_RENDERING_DIRECTX_CONFIGURATION_STRATEGY_H
#define NEXTGEN_ENGINE_RENDERING_DIRECTX_CONFIGURATION_STRATEGY_H

#include "components/configuration/config_manager.h"
#include "components/engine/nextgen_game_engine_interfaces.h"

namespace nextgen::engine::rendering::directx {

using interfaces::IConfigurationStrategy;

// NOLINTBEGIN(misc-non-private-member-variables-in-classes)
struct DirectXDefaultConfigStrategy
    : public interfaces::IConfigurationStrategy {
  bool Configure() override { return false; }

  configuration::ComponentConfig component_config_;
};
// NOLINTEND(misc-non-private-member-variables-in-classes)

}  // namespace nextgen::engine::rendering::directx

#endif
