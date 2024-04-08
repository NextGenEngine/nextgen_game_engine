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
      std::cerr << "Want to decode this: " << config << "\n";
      return config.as<ConfigType>();
    } catch (const YAML::Exception& e) {
      // Log the error and use default values on failure
      std::cerr << "Failed to decode config: " << e.what() << "\n";
      std::cerr << "It is current config state: "
                << configManager->GetConfigRootNode() << "\n";
      auto defaultConfig = getDefaultConfig();
      // Update the config node
      MergeYAMLNodes(config, YAML::Node(defaultConfig));
      // And a method in ConfigManager to save the configuration
      configManager->Save();
      return defaultConfig;
    }
  }

  void MergeYAMLNodes(YAML::Node currentConfig,
                      const YAML::Node& defaultConfig) {
    if (!defaultConfig.IsMap()) {
      currentConfig = defaultConfig;
      return;
    }

    if (!currentConfig.IsMap()) {
      currentConfig = defaultConfig;
      return;
    }

    for (YAML::const_iterator it = defaultConfig.begin();
         it != defaultConfig.end(); ++it) {
      std::string key = it->first.Scalar();
      YAML::Node defaultVal = it->second;

      // If the key does not exist in currentConfig, or if the key exists but
      // the corresponding value is not a map, replace the value in
      // currentConfig with the value from defaultConfig.
      if (!currentConfig[key] || !currentConfig[key].IsMap() ||
          !defaultVal.IsMap()) {
        currentConfig.remove(key);
        currentConfig[key] = defaultVal;
      } else if (currentConfig[key].IsMap() && defaultVal.IsMap()) {
        // If both current and default values for the key are maps, merge them
        // recursively.
        MergeYAMLNodes(currentConfig[key], defaultVal);
      }
      // If currentConfig has the key with a scalar value and defaultVal is also
      // scalar, the value in currentConfig has already been replaced above.
    }
  }
};

}  // namespace nextgen::engine::configuration

#endif
