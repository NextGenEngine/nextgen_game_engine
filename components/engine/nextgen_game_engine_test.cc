#include "nextgen_game_engine.h"

#include <yaml-cpp/node/parse.h>

#include <cstddef>
#include <cstdlib>
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

int SuccessfulExit(int code) {
  std::cout << "Successful exit"
            << "\n";
  return code;
}

int main() {
  auto component_config = InitConfigManager();
  if (!component_config) {
    return SuccessfulExit(EXIT_FAILURE);
  }

  // GameLoop(engine.value());

  // engine.reset();

  std::cout << "sizeof(NextGenEngine) = " << sizeof(NextGenEngine)
            << " bytes\n";

  try {
    nextgen::engine::ENGINE.Initialize(*component_config);
  } catch (...) {
    return SuccessfulExit(EXIT_FAILURE);
  }

  nextgen::engine::ENGINE.rendering_config_strategy_.Configure();

  // nextgen::engine::ENGINE.Loop();

  return SuccessfulExit(EXIT_SUCCESS);
}
