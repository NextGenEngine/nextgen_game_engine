#ifndef NEXTGEN_ENGINE_CONFIG_LOADER_H
#define NEXTGEN_ENGINE_CONFIG_LOADER_H

#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/yaml.h>

class IConfigLoader {
 public:
  virtual YAML::Node load() = 0;

  virtual ~IConfigLoader() = default;
};

// Factory function declaration
std::unique_ptr<IConfigLoader> CreateFileConfigLoader(
    const std::string& configFile);

#endif
