#include "config_loader.h"

class FileConfigLoader : public IConfigLoader {
 public:
  // Implement the Load function from the IConfigLoader interface
  YAML::Node load(const std::string &configFile) override {
    // The actual loading logic remains the same
    return YAML::LoadFile(configFile);
  }
};
