#include <yaml-cpp/exceptions.h>

#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <memory>
#include <optional>

#include "components/configuration/config_loader.h"
#include "components/configuration/config_manager.h"
#include "components/rendering/rendering.h"
#include "components/rendering/vulkan/vulkan_operations.h"

using nextgen::engine::configuration::ConfigManager;
using nextgen::engine::configuration::FileLoader;
using nextgen::engine::rendering::RenderingEngine;

auto CreateConfigManager() -> std::optional<ConfigManager> {
  while (true) {
    try {
      ConfigManager configManager(std::make_unique<FileLoader>("config.yaml"));
      return configManager;  // Successfully created, return it
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
      return std::nullopt;
    }
  }
}

int main() {
  auto config_manager = CreateConfigManager();
  if (!config_manager.has_value()) {
    return EXIT_FAILURE;
  }

  auto component_config = config_manager.value().getComponentConfig();

  const RenderingEngine rendering_engine(
      component_config.getSubConfig("rendering"));

  std::cout << (config_manager.value()["rendering"]["vulkan"]["refreshRate"]
                        .IsDefined()
                    ? "true"
                    : "false")
            << '\n';

  std::cout << "Vulkan config: "
            << config_manager.value()["rendering"]["vulkan"] << '\n';

  std::cout << "Successful exit.\n";
  return EXIT_SUCCESS;
}
