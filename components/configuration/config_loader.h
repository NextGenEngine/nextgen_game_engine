#ifndef NEXTGEN_ENGINE_CONFIG_LOADER_H
#define NEXTGEN_ENGINE_CONFIG_LOADER_H

#include <yaml-cpp/yaml.h>

class IConfigLoader {
 public:
  virtual ~IConfigLoader() = default;
  virtual YAML::Node load(const std::string &configFile) = 0;
};

// Factory function declaration
std::unique_ptr<IConfigLoader> CreateFileConfigLoader(
    const std::string &configFile);

#endif
