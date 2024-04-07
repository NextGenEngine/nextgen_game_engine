#include "config_manager.h"

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

ComponentConfig::ComponentConfig(ConfigManager* configManager,
                                 const YAML::Node& componentRootNode)
    : configManager(configManager), config(componentRootNode) {}

YAML::Node ComponentConfig::operator[](const std::string& key) {
  return config[key];
}

YAML::Node ComponentConfig::operator()() { return config; }

ComponentConfig ComponentConfig::getSubConfig(const std::string& path) {
  if (!config[path]) {
    config[path] = YAML::Node();
  }
  return ComponentConfig(configManager, config[path]);
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
  return ComponentConfig(this, config);
}
