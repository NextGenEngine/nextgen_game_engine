#include "nextgen_game_engine.h"

#include <yaml-cpp/exceptions.h>

#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <memory>
#include <utility>

#include "components/configuration/config_loader.h"
#include "components/configuration/config_manager.h"
#include "components/rendering/rendering.h"

namespace nextgen::engine {

using nextgen::engine::configuration::ConfigManager;
using nextgen::engine::configuration::IConfigLoader;
using nextgen::engine::rendering::RenderingEngine;

auto CreateConfigManager(std::unique_ptr<IConfigLoader> loader)
    -> std::shared_ptr<ConfigManager> {
  while (true) {
    try {
      return std::make_shared<ConfigManager>(
          std::move(loader));  // Successfully created, return it
    } catch (const YAML::BadFile& e) {
      std::cerr << "Failed to load or create the config file: " << e.what()
                << ". Retrying..." << '\n';
      // You might want to include a sleep here to prevent a tight retry loop
      std::ofstream const give_me_a_name("config.yaml");
      std::cerr << "Configuration file config.yaml created" << '\n';
    } catch (const YAML::ParserException& e) {
      std::cerr << "Configuration file was corrupted: " << e.what() << '\n';
      std::ofstream const give_me_a_name("config.yaml");
      std::cerr << "Default configuration file config.yaml created" << '\n';
    } catch (const std::exception& e) {
      std::cerr << "An unexpected error occurred: " << e.what() << '\n';
      throw;
      ;
    }
  }
}

NextGenEngine::NextGenEngine(std::unique_ptr<IConfigLoader> _loader)
    : configManager(CreateConfigManager(std::move(_loader))),
      renderingEngine(std::make_unique<RenderingEngine>(
          configManager->getComponentConfig().getSubConfig("rendering"))) {
  auto component_config = configManager->getComponentConfig();
  std::cout
      << (component_config["rendering"]["vulkan"]["refreshRate"].IsDefined()
              ? "true"
              : "false")
      << '\n';

  std::cout << "Vulkan config: " << component_config["rendering"]["vulkan"]
            << '\n';
}

void NextGenEngine::Loop() { renderingEngine->render(); }

}  // namespace nextgen::engine
