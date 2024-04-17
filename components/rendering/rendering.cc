#include "rendering.h"

#include <cctype>
#include <chrono>
#include <thread>

#include "components/rendering/rendering_config.h"

namespace nextgen::engine::rendering {

void RenderingEngine::ApplyConfiguration(const void* config) {
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-cstyle-cast,google-readability-casting)
  const auto* new_config = (RenderingEngineConfig*)config;
  SwitchApi(new_config->api);
  rendering_engine_config_ = *new_config;
}

void RenderingEngine::render() {
  std::this_thread::sleep_for(
      std::chrono::milliseconds(16));  // Simulate rendering time
}

}  // namespace nextgen::engine::rendering
