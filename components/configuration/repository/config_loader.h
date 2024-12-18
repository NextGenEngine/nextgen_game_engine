#ifndef NEXTGEN_ENGINE_CONFIG_LOADER_H
#define NEXTGEN_ENGINE_CONFIG_LOADER_H

#include <yaml-cpp/yaml.h>

#include <string>

#include "lib/std_ext.h"

namespace nextgen::engine::configuration {

using lib::std_ext::InterfaceBase;

// Abstract Interface for Config Loaders
struct IConfigLoader : InterfaceBase {
  virtual YAML::Node Load() = 0;
  virtual void Save(const YAML::Node* config) = 0;
};

// Loader for File-based Configuration
class FileLoader : public IConfigLoader {
 private:
  std::string m_file_path;

 public:
  explicit FileLoader(std::string file_path);

  YAML::Node Load() override;
  void Save(const YAML::Node* config) override;
};

// Loader for String-based Configuration
class StringLoader : public IConfigLoader {
 private:
  std::string m_yaml_content;

 public:
  explicit StringLoader(std::string yaml_content);

  YAML::Node Load() override;
  void Save(const YAML::Node* config) override;
};

}  // namespace nextgen::engine::configuration

#endif  // NEXTGEN_ENGINE_CONFIG_LOADER_H
