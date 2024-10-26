#include "nextgen_game_engine.h"

#include <yaml-cpp/node/parse.h>

#include <cstddef>
#include <cstdlib>
#include <exception>
#include <iostream>

#include "components/configuration/config_loader.h"
#include "components/configuration/config_manager.h"

using nextgen::engine::CONFIG_FILE_PATH;
using nextgen::engine::NextGenEngine;
using nextgen::engine::configuration::ConfigManager;

namespace {

nextgen::engine::configuration::FileLoader file_loader(CONFIG_FILE_PATH);
ConfigManager config_manager(file_loader);

int ExitProgram(int code) {
  std::cout << "Program exit"
            << "\n";
  return code;
}

int FailureExit() { return ExitProgram(EXIT_FAILURE); }
int SuccessExit() { return ExitProgram(EXIT_SUCCESS); }

}  // namespace

int main() {
  auto component_config = config_manager.GetRootComponentConfig();

  // GameLoop(engine.value());

  // engine.reset();

  std::cout << "sizeof(NextGenEngine) = " << sizeof(NextGenEngine)
            << " bytes\n";

  try {
    nextgen::engine::ENGINE.Initialize(component_config);
  } catch (std::exception& e) {
    std::cout << "MAIN: FATAL ERROR. Engine base initialization failed: "
              << e.what() << "\n";
    try {
      nextgen::engine::ENGINE.Shutdown();
    } catch (std::exception& e) {
      std::cout << "MAIN: FATAL ERROR. Engine shutdown failed: " << e.what()
                << "\n";
    }
    return FailureExit();
  }

  try {
    nextgen::engine::ENGINE.rendering_config_strategy_.Configure();
  } catch (std::exception& e) {
    std::cout << "MAIN: FATAL ERROR. Engine configuration failed: " << e.what();
    return FailureExit();
  }
  try {
    nextgen::engine::ENGINE.Loop();
  } catch (std::exception& e) {
    std::cout << "MAIN: FATAL ERROR. Engine Main loop throws exception: "
              << e.what();
    return FailureExit();
  }

  nextgen::engine::ENGINE.Shutdown();

  return SuccessExit();
}
