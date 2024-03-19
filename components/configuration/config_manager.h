#ifndef NEXTGEN_ENGINE_CONFIG_MANAGER_H
#define NEXTGEN_ENGINE_CONFIG_MANAGER_H

#include <yaml-cpp/yaml.h>

#include <string>

#include "config_loader.h"

class ConfigManager {
 private:
  YAML::Node config;

 public:
  explicit ConfigManager(std::unique_ptr<IConfigLoader> loader);

  template <typename T>
  T getSetting(const std::string &module, const std::string &setting) {
    return config[module][setting].as<T>();
  }
};

#endif
