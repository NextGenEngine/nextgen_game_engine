#include "components/configuration/config_manager.h"

#include <yaml-cpp/node/detail/iterator_fwd.h>
#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/type.h>

#include <string>

namespace nextgen::engine::configuration {

ComponentConfig ConfigManager::GetRootComponentConfig() {
  // If root node is not a Map, then make it a Map
  if (!rootNode_.IsMap()) {
    rootNode_ = YAML::Node(YAML::NodeType::Map);
  }
  return ComponentConfig(*this, rootNode_);
}

ComponentConfig ConfigManager::GetComponentConfig(
    const std::string& sectionName) {
  // If the node doesn't exist, create it
  if (!rootNode_[sectionName]) {
    rootNode_[sectionName] = YAML::Node(YAML::NodeType::Map);
  }
  return ComponentConfig(*this, rootNode_[sectionName]);
  // TODO(artem): try replace with helper. Read more in header file
  // return GetComponentConfigHelper(*this, rootNode_, sectionName);
}

ComponentConfig ComponentConfig::GetComponentConfig(
    const std::string& sectionName) {
  // If the node doesn't exist, create it
  if (!component_node_[sectionName]) {
    component_node_[sectionName] = YAML::Node(YAML::NodeType::Map);
  }
  return ComponentConfig(config_manager_, component_node_[sectionName]);
  // TODO(artem): try replace with helper. Read more in header file
  // return GetComponentConfigHelper(config_manager_, component_node_,
  //                                 sectionName);
}

ConfigManager& ComponentConfig::GetConfigManager() { return config_manager_; }

void ComponentConfig::MergeYAMLNodes(YAML::Node target,
                                     const YAML::Node& source) {
  if (!source.IsMap()) {
    target = source;
    return;
  }

  if (!target.IsMap()) {
    target = source;
    return;
  }

  for (YAML::const_iterator it = source.begin(); it != source.end(); ++it) {
    std::string const key = it->first.Scalar();
    YAML::Node const default_val = it->second;

    // If the key does not exist in currentConfig, or if the key exists but
    // the corresponding value is not a map, replace the value in
    // currentConfig with the value from defaultConfig.
    if (!target[key] || !target[key].IsMap() || !default_val.IsMap()) {
      target.remove(key);
      target[key] = default_val;
    } else if (target[key].IsMap() && default_val.IsMap()) {
      // If both current and default values for the key are maps, merge them
      // recursively.
      MergeYAMLNodes(target[key], default_val);
    }
    // If currentConfig has the key with a scalar value and defaultVal is also
    // scalar, the value in currentConfig has already been replaced above.
  }
}

}  // namespace nextgen::engine::configuration
