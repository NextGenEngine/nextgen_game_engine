#ifndef NEXTGEN_ENGINE_CONFIG_MANAGER_H
#define NEXTGEN_ENGINE_CONFIG_MANAGER_H

#include <yaml-cpp/yaml.h>

#include <string>

class ConfigManager {
 private:
  YAML::Node config;

 public:
  template <typename LoaderType>
  explicit ConfigManager(LoaderType loader,
                         const std::string &fileNameOrYamlContent);

  template <typename T>
  inline T getSetting(const std::string &module, const std::string &setting) {
    return config[module][setting].as<T>();
  }

  template <typename T>
  T getSetting_Not_Inline(const std::string &module,
                          const std::string &setting) {
    return config[module][setting].as<T>();
  }
};

ConfigManager ConfigManager_File(const std::string &fileName);
ConfigManager ConfigManager_String(const std::string &yamlContent);

#endif
