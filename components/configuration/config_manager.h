#ifndef NEXTGEN_ENGINE_CONFIG_MANAGER_H
#define NEXTGEN_ENGINE_CONFIG_MANAGER_H

#include <yaml-cpp/yaml.h>

#include <string>

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

template <typename T>
concept LoaderTypeConcept =
    requires(T api, const YAML::Node &config, const std::string &filePath) {
      { api.Load(filePath) } -> std::same_as<YAML::Node>;
      { api.Save(config) } -> std::same_as<void>;
      //   { api.loadConfig(configManager) } -> std::same_as<void>;
      //   { api.getState() } -> std::convertible_to<std::string>;
      //   { api.loadState(std::string{}) } -> std::same_as<void>;
      //   { api.loadDefaultConfig() } -> std::same_as<void>;
      //   { T(configManager) };  // Ensure constructible from ConfigManager
    };

template <LoaderTypeConcept LoaderType>
class ConfigManager {
 private:
  LoaderType loader;
  YAML::Node config;

 public:
  explicit inline ConfigManager(LoaderType loader,
                                const std::string &yamlStringOrString)
      : loader(loader), config(loader.Load(yamlStringOrString)) {}

  void Save() { loader.Save(config); }

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
  inline YAML::Node GetConfigRootNode() { return config; }

  inline ComponentConfig getComponentConfig() {
    if (config.IsNull()) {
      config = YAML::Load("{}");
    }
    return ComponentConfig(config);
  }
};

// ConfigManager &ConfigManager_File(const std::string &fileName);
// ConfigManager &ConfigManager_String(const std::string &yamlContent);

#endif
