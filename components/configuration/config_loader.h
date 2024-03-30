#ifndef NEXTGEN_ENGINE_CONFIG_LOADER_H
#define NEXTGEN_ENGINE_CONFIG_LOADER_H

#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/yaml.h>

/* NOTE: Curiously Recurring Template Pattern (CRTP)

   **How It Works**: ConfigLoader is a template that takes a LoaderType as its
     parameter. LoaderType is expected to be a derived class that implements a
     static loadImpl function. The load function then calls loadImpl, using
     static polymorphism. This is achieved by casting this to LoaderType* and
     calling the method directly.

  **Performance**: This method does not incur the runtime overhead
    associated with virtual function calls because the method to call is
    resolved at compile time. The compiler has complete information about the
    derived type (LoaderType) and can inline calls to loadImpl, further
    improving performance.

*/

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
