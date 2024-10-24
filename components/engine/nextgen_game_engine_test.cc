#include "nextgen_game_engine.h"

#include <yaml-cpp/node/parse.h>

#include <cstddef>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>

#include "components/configuration/config_loader.h"
#include "components/configuration/config_manager.h"

using nextgen::engine::CONFIG_FILE_PATH;
using nextgen::engine::NextGenEngine;
using nextgen::engine::configuration::ComponentConfig;
using nextgen::engine::configuration::ConfigManager;

auto GetDefaultConfig() -> std::string_view {
  // NOTE: there is no need to implement this function at the moment.
  // Each component have its own configuration. And I do not want to
  // know it on higher level. It gives me flexibility to easily
  // change component configuration without updating higher level
  // Engine component. Components become more encapsulated and decoupled
  // from higher level components.
  return "";
}

auto PrepareConfigFile(std::string_view config_file_path) {
  try {
    return YAML::LoadFile(std::string(config_file_path));
  } catch (...) {
    // If file does not exist, is invalid, or any error occurs, create a default
    // config
    std::cerr << "Creating default configuration file: " << config_file_path
              << '\n';
    std::ofstream outputFile((std::string(config_file_path)));
    if (!outputFile) {
      throw std::runtime_error("Unable to create default configuration file.");
    }
    const auto default_config = GetDefaultConfig();
    outputFile << default_config;
    if (!outputFile) {
      throw std::runtime_error("Unable to create default configuration file.");
    }
    return YAML::Node(default_config);
  }
}

auto InitConfigManager() -> std::optional<ComponentConfig> {
  try {
    // Prepare the configuration file
    auto config = PrepareConfigFile(CONFIG_FILE_PATH);
    // Create the configuration loader and manager
    auto loader = std::make_unique<nextgen::engine::configuration::FileLoader>(
        CONFIG_FILE_PATH);
    auto config_manager =
        std::make_shared<ConfigManager>(config, std::move(loader));

    return config_manager->getComponentConfig();
  } catch (...) {
    return std::nullopt;
  }
}

void GameLoop(std::unique_ptr<NextGenEngine>& engine) { engine->Loop(); }

int ExitProgram(int code) {
  std::cout << "Program exit"
            << "\n";
  return code;
}

int main() {
  auto component_config = InitConfigManager();
  if (!component_config) {
    return ExitProgram(EXIT_FAILURE);
  }

  // GameLoop(engine.value());

  // engine.reset();

  std::cout << "sizeof(NextGenEngine) = " << sizeof(NextGenEngine)
            << " bytes\n";

  try {
    nextgen::engine::ENGINE.Initialize(*component_config);
  } catch (std::exception& e) {
    std::cout << "FATAL ERROR: Engine base initialization failed: " << e.what()
              << "\n";
    try {
      nextgen::engine::ENGINE.Shutdown();
    } catch (std::exception& ee) {
      std::cout << "FATAL ERROR: Engine shutdown failed: " << ee.what() << "\n";
    }
    return ExitProgram(EXIT_FAILURE);
  }

  try {
    // nextgen::engine::ENGINE.rendering_config_strategy_.Configure();
  } catch (std::exception& e) {
    std::cout << "FATAL ERROR: Engine configuration failed: " << e.what();
    return ExitProgram(EXIT_FAILURE);
  }
  try {
    nextgen::engine::ENGINE.Loop();
  } catch (std::exception& e) {
  }

  nextgen::engine::ENGINE.Shutdown();

  return ExitProgram(EXIT_SUCCESS);
}
