#include "config_loader.h"

#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>

#include <string>

class FileConfigLoader : public IConfigLoader {
 public:
  // Implement the Load function from the IConfigLoader interface
  YAML::Node load(const std::string &configFile) override {
    // The actual loading logic remains the same
    return YAML::LoadFile(configFile);
  }
};
