#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/yaml.h>

#include <fstream>
#include <string>
#include <utility>  // Для std::move и std::forward

namespace move_semantics {

class FileLoader {
 private:
  std::string filePath;

 public:
  YAML::Node Load(const std::string& path) {
    filePath = path;
    return YAML::LoadFile(path);
  }

  void Save(YAML::Node&& config) const {
    std::ofstream outputStream(filePath);
    if (!outputStream) {
      throw std::runtime_error("Unable to open file for writing: " + filePath);
    }
    outputStream << config;
  }
};

class StringLoader {
 public:
  static YAML::Node Load(const std::string& yamlContent) {
    return YAML::Load(yamlContent);
  }

  // Поскольку сохранение для строки не имеет смысла, мы оставляем его пустым
  void Save(YAML::Node&& config) {}
};

class ComponentConfig {
 private:
  YAML::Node config;

 public:
  explicit ComponentConfig(YAML::Node&& componentRootNode)
      : config(componentRootNode) {}

  template <typename T>
  T getSetting(const std::string& setting) const {
    return config[setting].as<T>();
  }

  [[nodiscard]] YAML::Node operator[](const std::string& key) {
    return config[key];
  }
  [[nodiscard]] YAML::Node operator()() { return config; }

  [[nodiscard]] ComponentConfig getSubConfig(const std::string& path) {
    if (!config[path]) {
      config[path] = YAML::Node();
    }
    return ComponentConfig(config[path]);
  }
};

template <typename T>
concept LoaderTypeConcept =
    requires(T api, YAML::Node&& config, const std::string& filePath) {
      { api.Load(filePath) } -> std::same_as<YAML::Node>;
      { api.Save(std::move(config)) } -> std::same_as<void>;
    };

template <LoaderTypeConcept LoaderType>
class ConfigManager {
 private:
  LoaderType loader;
  YAML::Node config;

 public:
  explicit ConfigManager(LoaderType&& loader,
                         const std::string& yamlStringOrPath)
      : loader(std::forward<LoaderType>(loader)),
        config(this->loader.Load(yamlStringOrPath)) {}

  void Save() { loader.Save(std::move(config)); }

  template <typename T>
  T getSetting(const std::string& module) {
    return config[module].as<T>();
  }

  template <typename T>
  T getSetting_Not_Inline(const std::string& module,
                          const std::string& setting) {
    return config[module][setting].as<T>();
  }

  [[nodiscard]] YAML::Node operator[](const std::string& key) {
    return config[key];
  }
  [[nodiscard]] YAML::Node GetConfigRootNode() { return config; }

  [[nodiscard]] ComponentConfig getComponentConfig() {
    if (config.IsNull()) {
      config = YAML::Load("");
    }
    return ComponentConfig(std::move(config));
  }
};

}  // namespace move_semantics
