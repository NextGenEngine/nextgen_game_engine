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

ComponentConfig::ComponentConfig(std::shared_ptr<ConfigManager> config_manager,
                                 const YAML::Node& component_root_node)
    : m_config_manager(std::move(config_manager)),
      m_config(component_root_node) {}

YAML::Node ComponentConfig::operator[](const std::string& key) const {
  return m_config[key];
}

YAML::Node ComponentConfig::operator()() const { return m_config; }

ComponentConfig ComponentConfig::getSubConfig(const std::string& path) {
  if (!m_config[path]) {
    m_config[path] = YAML::Node();
  }
  return ComponentConfig(m_config_manager, m_config[path]);
}

void ComponentConfig::MergeYAMLNodes(YAML::Node current_config,
                                     const YAML::Node& new_config) {
  if (!new_config.IsMap()) {
    current_config = new_config;
    return;
  }

  if (!current_config.IsMap()) {
    current_config = new_config;
    return;
  }

  for (YAML::const_iterator it = new_config.begin(); it != new_config.end();
       ++it) {
    std::string const key = it->first.Scalar();
    YAML::Node const default_val = it->second;

    // If the key does not exist in currentConfig, or if the key exists but
    // the corresponding value is not a map, replace the value in
    // currentConfig with the value from defaultConfig.
    if (!current_config[key] || !current_config[key].IsMap() ||
        !default_val.IsMap()) {
      current_config.remove(key);
      current_config[key] = default_val;
    } else if (current_config[key].IsMap() && default_val.IsMap()) {
      // If both current and default values for the key are maps, merge them
      // recursively.
      MergeYAMLNodes(current_config[key], default_val);
    }
    // If currentConfig has the key with a scalar value and defaultVal is also
    // scalar, the value in currentConfig has already been replaced above.
  }
}

/*= == == == == == == == == == == == == == == == == == == ==
                    CONFIG MANAGER
= = == == == == == == == == == == == == == == == == == == ==*/

ConfigManager::ConfigManager(std::unique_ptr<IConfigLoader> loader)
    : m_loader(std::move(loader)), m_config(this->m_loader->Load()) {}

void ConfigManager::Save() { m_loader->Save(&m_config); }

YAML::Node ConfigManager::operator[](const std::string& key) {
  return m_config[key];
}

YAML::Node ConfigManager::GetConfigRootNode() { return m_config; }

ComponentConfig ConfigManager::getComponentConfig() {
  if (m_config.IsNull()) {
    m_config = YAML::Load("");
  }
  return ComponentConfig(shared_from_this(), m_config);
}
