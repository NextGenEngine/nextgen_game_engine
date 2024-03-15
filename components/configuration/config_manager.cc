#include "config_manager.h"

#include <exception>
#include <iostream>
#include <string>

ConfigManager::ConfigManager(std::unique_ptr<IConfigLoader> loader,
                             const std::string &configFile) {
  try {
    config = loader->load(configFile);
  } catch (const std::exception &e) {
    std::cerr << "Failed to load configuration: " << e.what() << std::endl;
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
