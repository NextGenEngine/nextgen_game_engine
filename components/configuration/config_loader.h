#ifndef NEXTGEN_ENGINE_CONFIG_LOADER_H
#define NEXTGEN_ENGINE_CONFIG_LOADER_H

#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/yaml.h>

class IConfigLoader {
 public:
  virtual ~IConfigLoader() = default;
  // Delete copy constructor and copy assignment operator
  IConfigLoader(const IConfigLoader&) = delete;
  IConfigLoader& operator=(const IConfigLoader&) = delete;

  // Optionally delete move constructor and move assignment operator
  // if you do not want your implementations of this interface to be movable.
  IConfigLoader(IConfigLoader&&) = delete;
  IConfigLoader& operator=(IConfigLoader&&) = delete;

  virtual YAML::Node load() = 0;
};

// Factory function declaration
std::unique_ptr<IConfigLoader> CreateFileConfigLoader(
    const std::string& configFile);

#endif
