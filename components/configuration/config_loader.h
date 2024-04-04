#ifndef NEXTGEN_ENGINE_CONFIG_LOADER_H
#define NEXTGEN_ENGINE_CONFIG_LOADER_H

#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/yaml.h>

#include <fstream>

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

// Specialization for loading from a file
class FileLoader {
 private:
  std::string filePath;

 public:
  inline YAML::Node Load(const std::string& filePath) {
    this->filePath = filePath;
    return YAML::LoadFile(filePath);
  }

  // Implementation of the save functionality for files
  inline void Save(const YAML::Node& config) const {
    std::ofstream outputStream(filePath);
    if (!outputStream) {
      throw std::runtime_error("Unable to open file for writing: " + filePath);
    }
    outputStream << config;
  }
};

// Specialization for loading from a string
class StringLoader {
 public:
  inline static YAML::Node Load(const std::string& yamlContent) {
    return YAML::Load(yamlContent);
  }

  inline void Save(const YAML::Node& config) {}
};

#endif
