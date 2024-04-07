#ifndef NEXTGEN_ENGINE_CONFIG_MANAGER_H
#define NEXTGEN_ENGINE_CONFIG_MANAGER_H

#include <yaml-cpp/yaml.h>

#include <iostream>
#include <memory>
#include <string>

#include "components/configuration/config_loader.h"

namespace nextgen::engine::configuration {

class ComponentConfig;

/*= == == == == == == == == == == == == == == == == == == ==
                    CONFIG MANAGER
= = == == == == == == == == == == == == == == == == == == ==*/

class ConfigManager {
 private:
  std::unique_ptr<IConfigLoader> loader;
  YAML::Node config;

 public:
  explicit ConfigManager(std::unique_ptr<IConfigLoader> loader);

  void Save();
  YAML::Node operator[](const std::string& key);
  YAML::Node GetConfigRootNode();
  ComponentConfig getComponentConfig();
};

/*= == == == == == == == == == == == == == == == == == == ==
                    COMPONENT CONFIG
= = == == == == == == == == == == == == == == == == == == ==*/

class ComponentConfig {
 private:
  ConfigManager* configManager;
  YAML::Node config;

 public:
  explicit ComponentConfig(ConfigManager* configManager,
                           const YAML::Node& componentRootNode);

  YAML::Node operator[](const std::string& key);
  YAML::Node operator()();
  ComponentConfig getSubConfig(const std::string& path);

  template <typename ConfigType>
  ConfigType LoadConfigOrDefault(std::function<ConfigType()> getDefaultConfig) {
    try {
      // Attempt to use the provided configuration
      return config.as<ConfigType>();
    } catch (const YAML::Exception& e) {
      // Log the error and use default values on failure
      std::cerr << "Failed to decode config: " << e.what() << "\n";
      auto defaultConfig = getDefaultConfig();
      // Update the config node
      config = defaultConfig;
      // And a method in ConfigManager to save the configuration
      configManager->Save();
      return defaultConfig;
    }
  }
};

}  // namespace nextgen::engine::configuration

#endif
