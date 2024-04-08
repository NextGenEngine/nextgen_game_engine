#include "config_manager.h"

#include <yaml-cpp/node/detail/iterator_fwd.h>
#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>

#include <memory>
#include <string>
#include <utility>

#include "config_loader.h"

using nextgen::engine::configuration::ComponentConfig;
using nextgen::engine::configuration::ConfigManager;
using nextgen::engine::configuration::IConfigLoader;

IConfigLoader::~IConfigLoader() = default;

/*= == == == == == == == == == == == == == == == == == == ==
                    COMPONENT CONFIG
= = == == == == == == == == == == == == == == == == == == ==*/

ComponentConfig::ComponentConfig(std::shared_ptr<ConfigManager> _configManager,
                                 const YAML::Node& componentRootNode)
    : configManager(std::move(_configManager)), config(componentRootNode) {}

YAML::Node ComponentConfig::operator[](const std::string& key) const {
  return config[key];
}

YAML::Node ComponentConfig::operator()() const { return config; }

ComponentConfig ComponentConfig::getSubConfig(const std::string& path) {
  if (!config[path]) {
    config[path] = YAML::Node();
  }
  return ComponentConfig(configManager, config[path]);
}

void ComponentConfig::MergeYAMLNodes(YAML::Node currentConfig,
                                     const YAML::Node& newConfig) {
  if (!newConfig.IsMap()) {
    currentConfig = newConfig;
    return;
  }

  if (!currentConfig.IsMap()) {
    currentConfig = newConfig;
    return;
  }

  for (YAML::const_iterator it = newConfig.begin(); it != newConfig.end();
       ++it) {
    std::string const key = it->first.Scalar();
    YAML::Node const defaultVal = it->second;

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

/*= == == == == == == == == == == == == == == == == == == ==
                    CONFIG MANAGER
= = == == == == == == == == == == == == == == == == == == ==*/

ConfigManager::ConfigManager(std::unique_ptr<IConfigLoader> loader)
    : loader(std::move(loader)), config(this->loader->Load()) {}

void ConfigManager::Save() { loader->Save(&config); }

YAML::Node ConfigManager::operator[](const std::string& key) {
  return config[key];
}

YAML::Node ConfigManager::GetConfigRootNode() { return config; }

ComponentConfig ConfigManager::getComponentConfig() {
  if (config.IsNull()) {
    config = YAML::Load("");
  }
  return ComponentConfig(shared_from_this(), config);
}
