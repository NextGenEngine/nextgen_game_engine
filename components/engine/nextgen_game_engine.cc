#include "nextgen_game_engine.h"

// #include <chrono>
#include <cstdlib>
#include <iostream>

// #include "oneapi/tbb/task_group.h"

namespace {
// void ProcessInput() {}

void update(auto delta) {}
}  // namespace

namespace nextgen::engine {

nextgen::engine::configuration::FileLoader file_loader(CONFIG_FILE_PATH);
NextGenEngine ENGINE;

void NextGenEngine::Loop() {
  rendering_engine_.MainLoop();
  // tbb::task_group taskGroup;

  // auto lastTime = std::chrono::high_resolution_clock::now();
  // double timeSinceLastUpdate = 0.0;
  // double const deltaTime = 1.0 / 60.0;  // Targeting 60 updates per second

  // // NOLINTNEXTLINE(bugprone-infinite-loop)
  // while (!rendering_engine_.Exiting()) {
  //   auto currentTime = std::chrono::high_resolution_clock::now();
  //   std::chrono::duration<double> const elapsed = currentTime - lastTime;
  //   lastTime = currentTime;
  //   timeSinceLastUpdate += elapsed.count();

  //   ProcessInput();

  //   while (timeSinceLastUpdate >= deltaTime) {
  //     update(deltaTime);
  //     timeSinceLastUpdate -= deltaTime;

  //     // Ensure the previous render task is completed before starting a new
  //     one taskGroup.wait();

  //     // Mark as ready for rendering and run rendering task
  //     taskGroup.run([this] { rendering_engine_.Render(); });

  //     // After starting the render task, main loop can proceed to the next
  //     // update or perform other tasks
  //   }

  //   // Wait for the last rendering task to complete before exiting or
  //   starting a
  //   // new frame
  //   taskGroup.wait();
  // }
}

void NextGenEngine::Initialize() {
  static bool initialized = false;
  if (initialized) {
    std::cerr << "Engine is already initialized! You cannot instantiate two "
                 "objects like this! Please use nextgen::engine::ENGINE global "
                 "variable to access main engine object\n";
  }

  std::cout << "NextGenEngine object is singleton. Its implemented as global "
               "variable visible to all translation units. All engine "
               "components and sub-components are direct part of engine "
               "singleton. So all their fields are available already before "
               "main. Here we just need to initialize its properties, before "
               "it can be configured and started\n";

  // rendering_config_strategy_.Initialize(component_config, rendering_engine_);

  std::cout << "NextGenGame engine factory done.\n";
  // rendering_engine_.apis_.vulkan_rendering_api.vulkan_config_.device_id = 5;
  // rendering_engine_.apis_.vulkan_rendering_api.vulkan_config_.height = 3;
  std::cout << "Device id="
            << rendering_engine_.apis_.vulkan_rendering_api.vulkan_device_
                   .m_vulkan_config.device_id
            << "\n";
  initialized = true;  // Set flag to indicate successful initialization
  std::cout << "Initialization complete.\n";
}

void NextGenEngine::Shutdown() { rendering_engine_.Shutdown(); }

}  // namespace nextgen::engine
