// config_repo.h
#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <yaml-cpp/yaml.h>

#include "components/configuration/repository/config_loader.h"

// NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members)
namespace nextgen::engine::configuration {

struct ConfigRepositoryNode;

struct ConfigRepository {
  explicit ConfigRepository(IConfigLoader& loader) : loader_(loader) {
    root_node_ = loader_.Load();
  }

  YAML::Node GetYamlNode() { return root_node_; }
  ConfigRepositoryNode GetNode();
  ConfigRepositoryNode GetNode(const std::string& sectionName);
  ConfigRepositoryNode operator[](const std::string& sectionName);
  void Save() { loader_.Save(&root_node_); }

 private:
  IConfigLoader& loader_;
  YAML::Node root_node_;
};

struct ConfigRepositoryNode {
  ConfigRepositoryNode(ConfigRepository& config_manager,
                       YAML::Node component_root_node)
      : config_repo_(config_manager), node_(component_root_node) {}

  // Returns a const reference to the component's configuration node
  const YAML::Node& GetYamlNode() const { return node_; }

  // Returns a mutable reference to the component's configuration node
  YAML::Node& GetYamlNodeMutable() { return node_; }

  // Template method to load configuration into a struct
  template <typename ConfigType>
  std::optional<ConfigType> LoadConfig() const {
    try {
      return std::make_optional(node_.as<ConfigType>());
    } catch (...) {
      // Handle parsing exceptions, return std::nullopt if parsing fails
      return std::nullopt;
    }
  }

  // Template method to update the configuration from a struct
  template <typename ConfigType>
  void UpdateConfig(const ConfigType& new_config) {
    MergeYAMLNodes(node_, YAML::Node(new_config));
  }

  // Saves the updated configuration back to the ConfigManager
  void Save() {
    // Update the root node in ConfigManager and invoke save
    config_repo_.Save();
  }

  // Get a sub-component configuration
  ConfigRepositoryNode GetNode(const std::string& sectionName);
  ConfigRepositoryNode operator[](const std::string& sectionName);
  ConfigRepository& GetConfigRepository();

  void MergeYAMLNodes(YAML::Node target, const YAML::Node& source);

  // Copy assignment operator
  ConfigRepositoryNode& operator=(const ConfigRepositoryNode& other) {
    if (this != &other) {  // Check for self-assignment
      // Assign the component_node_ as in the copy constructor
      node_ = other.node_;
      // Note: config_manager_ is a reference and remains bound to the original
      // ConfigManager, so we do not attempt to reassign it.
    }
    return *this;
  }

 private:
  ConfigRepository& config_repo_;
  YAML::Node node_;
};

// TODO(artem): try to use this function to replace duplication of code in
// ConfigManager::GetComponentConfig and ComponentConfig::GetComponentConfig
// methods. But I do not like additional call (in fact ComponentConfig will be
// only used most of the time in real applications), so check first compiled
// binary, if inlining will work here
inline ConfigRepositoryNode GetComponentConfigHelper(
    ConfigRepository& parent, YAML::Node& startNode,
    const std::string& sectionName) {
  if (!startNode[sectionName]) {
    startNode[sectionName] = YAML::Node(YAML::NodeType::Map);
  }
  return ConfigRepositoryNode(parent, startNode[sectionName]);
}

}  // namespace nextgen::engine::configuration
// NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members)

#endif  // CONFIG_MANAGER_H
