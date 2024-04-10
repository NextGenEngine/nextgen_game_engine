#include "nextgen_game_engine.h"

#include <cstdlib>
#include <memory>
#include <utility>

#include "components/configuration/config_manager.h"
#include "components/rendering/rendering.h"

namespace nextgen::engine {

using nextgen::engine::configuration::ConfigManager;
using nextgen::engine::rendering::RenderingEngine;

NextGenEngine::NextGenEngine(std::shared_ptr<ConfigManager> config_manager,
                             std::unique_ptr<RenderingEngine> rendering_engine)
    : m_config_manager(std::move(config_manager)),
      m_rendering_engine(std::move(rendering_engine)) {}

void NextGenEngine::Loop() { m_rendering_engine->render(); }

}  // namespace nextgen::engine
