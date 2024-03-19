#include "config_loader.h"

#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>

#include <memory>
#include <string>
#include <utility>

class FileConfigLoader : public IConfigLoader {
 public:
  explicit FileConfigLoader(std::string configFile)
      : configFile(std::move(configFile)) {}
  // Implement the Load function from the IConfigLoader interface
  YAML::Node load() override {
    // The actual loading logic remains the same
    return YAML::LoadFile(configFile);
  }

 private:
  std::string configFile;
};

// Factory function declaration
std::unique_ptr<IConfigLoader> CreateFileConfigLoader(
    const std::string &configFile) {
  return std::make_unique<FileConfigLoader>(configFile);
}
