#include "nextgen_game_engine.h"

#include <chrono>
#include <cstdlib>
#include <memory>
#include <utility>

#include "components/configuration/config_manager.h"
#include "components/rendering/rendering.h"
#include "oneapi/tbb/global_control.h"
#include "oneapi/tbb/task_group.h"
#include "oneapi/tbb/tick_count.h"

namespace nextgen::engine {

using nextgen::engine::configuration::ConfigManager;
using nextgen::engine::rendering::RenderingEngine;

NextGenEngine::NextGenEngine(std::shared_ptr<ConfigManager> config_manager,
                             std::unique_ptr<RenderingEngine> rendering_engine)
    : m_config_manager(std::move(config_manager)),
      m_rendering_engine(std::move(rendering_engine)) {}

void ProcessInput() {}

void update(auto delta) {}

void NextGenEngine::Loop() {
  tbb::task_group taskGroup;

  auto lastTime = std::chrono::high_resolution_clock::now();
  double timeSinceLastUpdate = 0.0;
  double const deltaTime = 1.0 / 60.0;  // Targeting 60 updates per second

  auto isExiting = false;

  while (!isExiting) {
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> const elapsed = currentTime - lastTime;
    lastTime = currentTime;
    timeSinceLastUpdate += elapsed.count();

    ProcessInput();

    while (timeSinceLastUpdate >= deltaTime) {
      update(deltaTime);
      timeSinceLastUpdate -= deltaTime;

      // Ensure the previous render task is completed before starting a new one
      taskGroup.wait();

      // Mark as ready for rendering and run rendering task
      taskGroup.run([this] { m_rendering_engine->render(); });

      // After starting the render task, main loop can proceed to the next
      // update or perform other tasks
    }

    // Wait for the last rendering task to complete before exiting or starting a
    // new frame
    taskGroup.wait();
  }
}

}  // namespace nextgen::engine
