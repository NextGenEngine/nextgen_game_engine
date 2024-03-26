#ifndef NEXTGEN_ENGINE_CONFIG_LOADER_H
#define NEXTGEN_ENGINE_CONFIG_LOADER_H

#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/yaml.h>

// Abstract base ConfigLoader class template
template <typename LoaderType>
class ConfigLoader {
 public:
  YAML::Node load(const std::string& fileNameOrYamlStr) {
    // Forward the call to the loader-specific load implementation
    return static_cast<LoaderType*>(this)->loadImpl(fileNameOrYamlStr);
  }
};

// Specialization for loading from a file
class FileLoader : public ConfigLoader<FileLoader> {
 public:
  static YAML::Node loadImpl(const std::string& filePath) {
    return YAML::LoadFile(filePath);
  }
};

// Specialization for loading from a string
class StringLoader : public ConfigLoader<StringLoader> {
 public:
  static YAML::Node loadImpl(const std::string& yamlContent) {
    return YAML::Load(yamlContent);
  }
};

#endif
