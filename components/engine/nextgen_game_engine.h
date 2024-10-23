#ifndef NEXTGEN_GAME_ENGINE__H
#define NEXTGEN_GAME_ENGINE__H

#include <iostream>

#include "components/configuration/config_loader.h"
#include "components/configuration/config_manager.h"
#include "components/engine/nextgen_game_engine_templates.h"
#include "components/rendering/config_strategy/rendering_config_strategy.h"
#include "components/rendering/rendering_engine.h"

namespace nextgen::engine {

using configuration::ComponentConfig;
using configuration::IConfigLoader;
using rendering::RenderingConfigurationPrimaryStrategy;
using rendering::RenderingConfigurationStrategy;
using rendering::RenderingEngine;
using templates::FallbackConfigurationStrategyTemplate;

constexpr std::string_view CONFIG_FILE_PATH = "config.yaml";

// NOLINTBEGIN(misc-non-private-member-variables-in-classes)
struct NextGenEngine {
  explicit NextGenEngine() { std::cout << "NextGenEngine object created\n"; }
  void Loop();
  void Initialize(ComponentConfig component_config);
  void Shutdown();

  ComponentConfig component_config_;
  RenderingEngine rendering_engine_;

  RenderingConfigurationStrategy rendering_config_strategy_;
  // RenderingConfigurationStrategy rendering_config_strategy_;
};
// NOLINTEND(misc-non-private-member-variables-in-classes)

// GLOBAL VARIABLE AS SINGLETON (instead of singleton as static method variable)
extern NextGenEngine ENGINE;

}  // namespace nextgen::engine

#endif
