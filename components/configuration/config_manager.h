#ifndef NEXTGEN_ENGINE_CONFIG_MANAGER_H
#define NEXTGEN_ENGINE_CONFIG_MANAGER_H

#include <yaml-cpp/yaml.h>

#include <string>

class ConfigManager;

class ComponentConfig {
 private:
  YAML::Node config;

 public:
  explicit inline ComponentConfig(YAML::Node componentRootNode)
      : config(componentRootNode) {}

  template <typename T>
  inline T getSetting(const std::string &setting) const {
    return config[setting].as<T>();
  }

  inline YAML::Node operator[](const std::string &key) { return config[key]; }
  inline YAML::Node operator()() { return config; }

  inline ComponentConfig getSubConfig(const std::string &path) {
    if (!config[path]) {
      config[path] = YAML::Node();
    }
    return ComponentConfig(config[path]);
  }
};

class ConfigManager {
 private:
  YAML::Node config;

 public:
  template <typename LoaderType>
  explicit inline ConfigManager(LoaderType loader,
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

  inline YAML::Node operator[](const std::string &key) { return config[key]; }

  inline ComponentConfig getComponentConfig() {
    if (config.IsNull()) {
      config = YAML::Load("{}");
    }
    return ComponentConfig(config);
  }
};

ConfigManager ConfigManager_File(const std::string &fileName);
ConfigManager ConfigManager_String(const std::string &yamlContent);

#endif
