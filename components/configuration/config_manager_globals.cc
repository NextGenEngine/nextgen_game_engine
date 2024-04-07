#include "config_manager_globals.h"

#include <yaml-cpp/exceptions.h>

#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>

#include "config_loader.h"
#include "config_manager.h"

auto CreateConfigManager() -> ConfigManager<FileLoader> {
  while (true) {
    try {
      return ConfigManager(FileLoader(), "config.yaml");
    } catch (const YAML::BadFile& e) {
      std::cerr << "Failed to load or create the config file: " << e.what()
                << ". Retrying..." << '\n';
      // You might want to include a sleep here to prevent a tight retry loop
      std::ofstream const give_me_a_name("config.yaml");
      std::cerr << "Configuration file config.yaml created" << '\n';
    } catch (const std::exception& e) {
      std::cerr << "An unexpected error occurred: " << e.what() << '\n';
      exit(1);
    }
  }
}

ConfigManager<FileLoader> CONFIG_MANAGER = CreateConfigManager();
