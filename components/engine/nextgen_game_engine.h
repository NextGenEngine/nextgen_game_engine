#ifndef NEXTGEN_GAME_ENGINE__H
#define NEXTGEN_GAME_ENGINE__H

#include "components/configuration/config_loader.h"
#include "components/configuration/config_manager.h"
#include "components/rendering/rendering.h"

namespace nextgen::engine {
using configuration::ConfigManager;
using configuration::IConfigLoader;
using rendering::RenderingEngine;

class NextGenEngine {
  configuration::ConfigManager configManager;
  std::unique_ptr<RenderingEngine> renderingEngine;

 public:
  explicit NextGenEngine(std::unique_ptr<IConfigLoader> _loader);
};

}  // namespace nextgen::engine

#endif