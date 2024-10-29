#include "nextgen_game_engine.h"

#include <yaml-cpp/node/parse.h>

#include <cstddef>
#include <cstdlib>
#include <exception>
#include <iostream>

using nextgen::engine::NextGenEngine;

namespace {

int ExitProgram(int code) {
  std::cout << "Program exit"
            << "\n";
  return code;
}

int FailureExit() { return ExitProgram(EXIT_FAILURE); }
int SuccessExit() { return ExitProgram(EXIT_SUCCESS); }

void TryToShutdown() {
  try {
    nextgen::engine::ENGINE.Shutdown();
  } catch (std::exception& e) {
    std::cout << "MAIN: FATAL ERROR. Engine shutdown failed: " << e.what()
              << "\n";
  }
}

}  // namespace

int main() {
  std::cout << "sizeof(NextGenEngine) = " << sizeof(NextGenEngine)
            << " bytes\n";

  try {
    nextgen::engine::ENGINE.Initialize();
  } catch (std::exception& e) {
    std::cout << "MAIN: FATAL ERROR. Engine base initialization failed: "
              << e.what() << "\n";
    TryToShutdown();
    return FailureExit();
  }

  try {
    nextgen::engine::ENGINE.rendering_config_strategy_.Configure();
    std::cout << "Device id="
              << nextgen::engine::ENGINE.rendering_engine_.apis_
                     .vulkan_rendering_api.vulkan_config_.device_id
              << "\n";
  } catch (std::exception& e) {
    std::cout << "MAIN: FATAL ERROR. Engine configuration failed: " << e.what();
    TryToShutdown();
    return FailureExit();
  }
  try {
    nextgen::engine::ENGINE.Loop();
  } catch (std::exception& e) {
    std::cout << "MAIN: FATAL ERROR. Engine Main loop throws exception: "
              << e.what();
    TryToShutdown();
    return FailureExit();
  }

  nextgen::engine::ENGINE.Shutdown();

  return SuccessExit();
}
