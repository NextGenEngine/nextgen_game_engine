#include "nextgen_game_engine.h"

#include <chrono>
#include <cstdlib>

#include "oneapi/tbb/task_group.h"

namespace nextgen::engine {

NextGenEngine ENGINE;

void ProcessInput() {}

void update(auto delta) {}

void NextGenEngine::Loop() {
  tbb::task_group taskGroup;

  auto lastTime = std::chrono::high_resolution_clock::now();
  double timeSinceLastUpdate = 0.0;
  double const deltaTime = 1.0 / 60.0;  // Targeting 60 updates per second

  // NOLINTNEXTLINE(bugprone-infinite-loop)
  while (!rendering_engine_.Exiting()) {
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
      taskGroup.run([this] { rendering_engine_.Render(); });

      // After starting the render task, main loop can proceed to the next
      // update or perform other tasks
    }

    // Wait for the last rendering task to complete before exiting or starting a
    // new frame
    taskGroup.wait();
  }
}

}  // namespace nextgen::engine
