#ifndef NEXTGEN_GAME_ENGINE__H
#define NEXTGEN_GAME_ENGINE__H

#include "components/configuration/config_loader.h"
#include "components/configuration/config_manager.h"
#include "components/rendering/rendering.h"

namespace nextgen::engine {
using configuration::ConfigManager;
using configuration::IConfigLoader;
using rendering::RenderingEngine;

constexpr std::string_view CONFIG_FILE_PATH = "config.yaml";

class NextGenEngine {
  std::shared_ptr<ConfigManager> m_config_manager;
  std::unique_ptr<RenderingEngine> m_rendering_engine;

 public:
  explicit NextGenEngine(std::shared_ptr<ConfigManager> config_manager,
                         std::unique_ptr<RenderingEngine> rendering_engine);
  void Loop();
};

}  // namespace nextgen::engine

#endif
