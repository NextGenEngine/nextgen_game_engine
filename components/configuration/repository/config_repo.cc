#include "config_repo.h"

#include <yaml-cpp/node/detail/iterator_fwd.h>
#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/type.h>

#include <string>

namespace nextgen::engine::configuration {

ConfigRepositoryNode ConfigRepository::GetNode() {
  // If root node is not a Map, then make it a Map
  if (!root_node_.IsMap()) {
    root_node_ = YAML::Node(YAML::NodeType::Map);
  }
  return ConfigRepositoryNode(*this, root_node_);
}

ConfigRepositoryNode ConfigRepository::GetNode(const std::string& sectionName) {
  // If the node doesn't exist, create it
  if (!root_node_[sectionName]) {
    root_node_[sectionName] = YAML::Node(YAML::NodeType::Map);
  }
  return ConfigRepositoryNode(*this, root_node_[sectionName]);
  // TODO(artem): try replace with helper. Read more in header file
  // return GetComponentConfigHelper(*this, rootNode_, sectionName);
}

ConfigRepositoryNode ConfigRepository::operator[](
    const std::string& sectionName) {
  return GetNode(sectionName);
}

ConfigRepositoryNode ConfigRepositoryNode::GetNode(
    const std::string& sectionName) {
  // If the node doesn't exist, create it
  if (!node_[sectionName]) {
    node_[sectionName] = YAML::Node(YAML::NodeType::Map);
  }
  return ConfigRepositoryNode(config_repo_, node_[sectionName]);
  // TODO(artem): try replace with helper. Read more in header file
  // return GetComponentConfigHelper(config_manager_, component_node_,
  //                                 sectionName);
}

ConfigRepositoryNode ConfigRepositoryNode::operator[](
    const std::string& sectionName) {
  return GetNode(sectionName);
}

ConfigRepository& ConfigRepositoryNode::GetConfigRepository() {
  return config_repo_;
}

void ConfigRepositoryNode::MergeYAMLNodes(YAML::Node target,
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
