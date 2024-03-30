#ifndef NEXTGEN_ENGINE_CONFIG_MANAGER_H
#define NEXTGEN_ENGINE_CONFIG_MANAGER_H

#include <yaml-cpp/yaml.h>

#include <string>

class ConfigManager;

class ComponentConfig {
 private:
  const YAML::Node &config;

 public:
  // Constructor now takes just a YAML::Node
  explicit ComponentConfig(const YAML::Node &componentRootNode)
      : config(componentRootNode) {}

  template <typename T>
  inline T getSetting(const std::string &setting) {
    return config[setting].as<T>();
  }

  ComponentConfig getSubConfig(const std::string &path) const {
    const YAML::Node &subNode = config[path];
    return ComponentConfig(subNode);
  }

  // Delete copy constructor and copy assignment operator
  ComponentConfig(const ComponentConfig &) = delete;
  ComponentConfig &operator=(const ComponentConfig &) = delete;
  ~ComponentConfig() = default;  // Default destructor
  ComponentConfig(ComponentConfig &&) = delete;
  ComponentConfig &operator=(ComponentConfig &&) = delete;
};

class ConfigManager {
 private:
  YAML::Node config;

 public:
  template <typename LoaderType>
  explicit ConfigManager(LoaderType loader,
                         const std::string &fileNameOrYamlContent);

  // DEPRECATED: use ComponentConfigManager, because module config can
  // have more then one level depth
  template <typename T>
  inline T getSetting(const std::string &module, const std::string &setting) {
    return config[module][setting].as<T>();
  }

  template <typename T>
  inline T getSetting(const std::string &module) {
    return config[module].as<T>();
  }

  template <typename T>
  T getSetting_Not_Inline(const std::string &module,
                          const std::string &setting) {
    return config[module][setting].as<T>();
  }

  ComponentConfig getComponentConfig() const { return ComponentConfig(config); }
};

ConfigManager ConfigManager_File(const std::string &fileName);
ConfigManager ConfigManager_String(const std::string &yamlContent);

#endif
