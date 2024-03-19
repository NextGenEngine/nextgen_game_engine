#include "config_manager.h"

#include <exception>
#include <iostream>
#include <memory>

#include "components/configuration/config_loader.h"

ConfigManager::ConfigManager(std::unique_ptr<IConfigLoader> loader) {
  try {
    config = loader->load();
  } catch (const std::exception &e) {
    std::cerr << "Failed to load configuration: " << e.what() << '\n';
    throw;
  }
}

// // Usage
// int main() {
//   ConfigManager configManager("config.yaml");

//   auto resolution =
//       configManager.getSetting<std::string>("graphics", "resolution");
//   auto volume = configManager.getSetting<int>("audio", "volume");

//   std::cout << "Graphics Resolution: " << resolution << std::endl;
//   std::cout << "Audio Volume: " << volume << std::endl;

//   return 0;
// }
