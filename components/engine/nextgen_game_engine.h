#ifndef NEXTGEN_GAME_ENGINE__H
#define NEXTGEN_GAME_ENGINE__H

#include <iostream>

#include "components/configuration/orchestrator/config_orchestrator.h"
#include "components/configuration/repository/config_loader.h"
#include "components/configuration/repository/config_repo.h"
#include "components/engine/nextgen_game_engine_templates.h"
#include "components/rendering/rendering_engine.h"

namespace nextgen::engine {

using configuration::ConfigRepository;
using configuration::ConfigRepositoryNode;
using configuration::IConfigLoader;
using rendering::RenderingEngine;
using templates::FallbackConfigurationStrategyTemplate;

constexpr std::string_view CONFIG_FILE_PATH = "config.yaml";
extern nextgen::engine::configuration::FileLoader file_loader;

// NOLINTBEGIN(misc-non-private-member-variables-in-classes)
struct NextGenEngine {
  explicit NextGenEngine()
      : component_config_(file_loader),
        rendering_config_strategy_(component_config_, rendering_engine_) {
    std::cout << "NextGenEngine object created\n";
  }
  void Loop();
  static void Initialize();
  void Shutdown();

  ConfigRepository component_config_{file_loader};
  RenderingEngine rendering_engine_;
  configuration::ConfigOrchestrator rendering_config_strategy_;
};
// NOLINTEND(misc-non-private-member-variables-in-classes)

// GLOBAL VARIABLE AS SINGLETON (instead of singleton as static method variable)
extern NextGenEngine ENGINE;

}  // namespace nextgen::engine

#endif
