#include <yaml-cpp/yaml.h>

#include <exception>
#include <iostream>
#include <string>

class ConfigManager {
 private:
  YAML::Node config;

 public:
  explicit ConfigManager(const std::string& configFile) {
    try {
      config = YAML::LoadFile(configFile);
    } catch (const std::exception& e) {
      std::cerr << "Failed to load configuration: " << e.what() << std::endl;
      throw;
    }
  }

  template <typename T>
  T getSetting(const std::string& module, const std::string& setting) {
    return config[module][setting].as<T>();
  }
};
