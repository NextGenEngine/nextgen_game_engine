#include "components/engine/nextgen_game_engine.h"

#include <yaml-cpp/node/parse.h>

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
#include "components/rendering/rendering.h"

using nextgen::engine::CONFIG_FILE_PATH;
using nextgen::engine::NextGenEngine;
using nextgen::engine::configuration::ConfigManager;
using nextgen::engine::rendering::RenderingEngine;

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
    std::ofstream outputFile(config_file_path);
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

auto InitEngine() -> std::optional<std::unique_ptr<NextGenEngine>> {
  try {
    // Prepare the configuration file
    auto config = PrepareConfigFile(CONFIG_FILE_PATH);
    // Create the configuration loader and manager
    auto loader = std::make_unique<nextgen::engine::configuration::FileLoader>(
        CONFIG_FILE_PATH);
    auto config_manager =
        std::make_shared<ConfigManager>(config, std::move(loader));

    // Create the rendering engine with the config manager
    auto rendering_component_config =
        config_manager->getComponentConfig().getSubConfig("rendering");
    auto rendering_engine =
        std::make_unique<RenderingEngine>(rendering_component_config);

    // Create the game engine with its dependencies
    return std::make_unique<NextGenEngine>(std::move(config_manager),
                                           std::move(rendering_engine));
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
  auto engine = InitEngine();
  if (!engine) {
    return SuccessfulExit(EXIT_FAILURE);
  }

  GameLoop(engine.value());

  engine.reset();

  return SuccessfulExit(EXIT_SUCCESS);
}
