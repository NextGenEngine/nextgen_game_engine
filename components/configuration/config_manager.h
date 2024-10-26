// config_manager.h
#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <yaml-cpp/yaml.h>

#include "components/configuration/config_loader.h"

// NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members)
namespace nextgen::engine::configuration {

struct ComponentConfig;

struct ConfigManager {
  explicit ConfigManager(IConfigLoader& loader) : loader_(loader) {
    rootNode_ = loader_.Load();
  }

  YAML::Node GetRootNode() { return rootNode_; }
  ComponentConfig GetRootComponentConfig();
  ComponentConfig GetComponentConfig(const std::string& sectionName);
  void Save() { loader_.Save(&rootNode_); }

 private:
  IConfigLoader& loader_;
  YAML::Node rootNode_;
};

struct ComponentConfig {
  ComponentConfig(ConfigManager& config_manager, YAML::Node component_root_node)
      : config_manager_(config_manager), component_node_(component_root_node) {}

  // Returns a const reference to the component's configuration node
  const YAML::Node& GetNode() const { return component_node_; }

  // Returns a mutable reference to the component's configuration node
  YAML::Node& GetMutableNode() { return component_node_; }

  // Template method to load configuration into a struct
  template <typename ConfigType>
  std::optional<ConfigType> LoadConfig() const {
    try {
      return std::make_optional(component_node_.as<ConfigType>());
    } catch (...) {
      // Handle parsing exceptions, return std::nullopt if parsing fails
      return std::nullopt;
    }
  }

  // Template method to update the configuration from a struct
  template <typename ConfigType>
  void UpdateConfig(const ConfigType& new_config) {
    MergeYAMLNodes(component_node_, YAML::Node(new_config));
    // component_node_ = YAML::convert<ConfigType>::encode(new_config);
  }

  // Saves the updated configuration back to the ConfigManager
  void Save() {
    // Update the root node in ConfigManager and invoke save
    config_manager_.Save();
  }

  // Get a sub-component configuration
  ComponentConfig GetComponentConfig(const std::string& sectionName);
  ConfigManager& GetConfigManager();

  void MergeYAMLNodes(YAML::Node target, const YAML::Node& source);

  // Copy assignment operator
  ComponentConfig& operator=(const ComponentConfig& other) {
    if (this != &other) {  // Check for self-assignment
      // Assign the component_node_ as in the copy constructor
      component_node_ = other.component_node_;
      // Note: config_manager_ is a reference and remains bound to the original
      // ConfigManager, so we do not attempt to reassign it.
    }
    return *this;
  }

 private:
  ConfigManager& config_manager_;
  YAML::Node component_node_;
};

// TODO(artem): try to use this function to replace duplication of code in
// ConfigManager::GetComponentConfig and ComponentConfig::GetComponentConfig
// methods. But I do not like additional call (in fact ComponentConfig will be
// only used most of the time in real applications), so check first compiled
// binary, if inlining will work here
inline ComponentConfig GetComponentConfigHelper(
    ConfigManager& parent, YAML::Node& startNode,
    const std::string& sectionName) {
  if (!startNode[sectionName]) {
    startNode[sectionName] = YAML::Node(YAML::NodeType::Map);
  }
  return ComponentConfig(parent, startNode[sectionName]);
}

}  // namespace nextgen::engine::configuration
// NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members)

#endif  // CONFIG_MANAGER_H
