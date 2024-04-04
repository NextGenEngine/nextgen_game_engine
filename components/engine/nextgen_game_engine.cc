#include "nextgen_game_engine.h"

#include <yaml-cpp/exceptions.h>

#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <optional>

#include "components/configuration/config_loader.h"
#include "components/configuration/config_manager.h"
#include "components/rendering/vulkan/vulkan_rendering.h"

auto createConfigManager() -> std::optional<ConfigManager<FileLoader>> {
  while (true) {
    try {
      auto configManager = ConfigManager(FileLoader(), "config.yaml");
      return configManager;  // Successfully created, return it
    } catch (const YAML::BadFile& e) {
      std::cerr << "Failed to load or create the config file: " << e.what()
                << ". Retrying..." << '\n';
      // You might want to include a sleep here to prevent a tight retry loop
      std::ofstream const give_me_a_name("config.yaml");
      std::cerr << "Configuration file config.yaml created" << '\n';
    } catch (const std::exception& e) {
      std::cerr << "An unexpected error occurred: " << e.what() << '\n';
      return std::nullopt;
    }
  }
}

int main() {
  auto configManager = createConfigManager();
  if (!configManager.has_value()) {
    vulkan_cleanup();
    return EXIT_FAILURE;
  }
  try {
    auto currentContext = createSystemContextWithLoader(
        (*configManager).getComponentConfig(), *configManager);
  } catch (const std::exception& e) {
    std::cerr << "An unexpected error occurred: " << e.what() << '\n';
  }
  vulkan_create_device();
  vulkan_create_swapchain();
  vulkan_cleanup();

  std::cout
      << ((*configManager)["rendering"]["vulkan"]["refreshRate"].IsDefined()
              ? "true"
              : "false")
      << '\n';

  std::cout << "Vulkan config: " << (*configManager)["rendering"]["vulkan"]
            << '\n';
  return EXIT_SUCCESS;
}
