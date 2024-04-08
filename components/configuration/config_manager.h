#ifndef NEXTGEN_ENGINE_CONFIG_MANAGER_H
#define NEXTGEN_ENGINE_CONFIG_MANAGER_H

#include <yaml-cpp/yaml.h>

#include <memory>
#include <optional>
#include <string>

#include "components/configuration/config_loader.h"

namespace nextgen::engine::configuration {

class ComponentConfig;

/*= == == == == == == == == == == == == == == == == == == ==
                    CONFIG MANAGER
= = == == == == == == == == == == == == == == == == == == ==*/

class ConfigManager : public std::enable_shared_from_this<ConfigManager> {
 private:
  std::unique_ptr<IConfigLoader> loader;
  YAML::Node config;

 public:
  explicit ConfigManager(std::unique_ptr<IConfigLoader> loader);

  void Save();
  YAML::Node operator[](const std::string& key);
  YAML::Node GetConfigRootNode();
  ComponentConfig getComponentConfig();
};

/*= == == == == == == == == == == == == == == == == == == ==
                    COMPONENT CONFIG
= = == == == == == == == == == == == == == == == == == == ==*/

class ComponentConfig {
 public:
  explicit ComponentConfig(std::shared_ptr<ConfigManager> configManager,
                           const YAML::Node& componentRootNode);

  YAML::Node operator[](const std::string& key) const;
  YAML::Node operator()() const;
  ComponentConfig getSubConfig(const std::string& path);

  template <typename ConfigType>
  std::optional<ConfigType> LoadConfig() const {
    try {
      return config.as<ConfigType>();
    } catch (const YAML::Exception& e) {
      return std::nullopt;
    } catch (...) {
      throw;
    }
  }

  /**
   * Updates the existing configuration by merging the provided configuration
   * data into it. This operation attempts to intelligently merge the new
   * configuration data with the existing configuration state, ensuring that
   * updates are applied while preserving the overall structure and existing
   * data where possible. In case of incompatible data types or structures
   * between the existing and new configuration, the method tries to replace the
   * problematic segments with the new configuration data.
   *
   * The merging strategy is primarily designed to handle complex configuration
   * structures gracefully, including nested maps and lists. However, specific
   * merge behavior, especially for deeply nested structures or custom types,
   * might depend on the implementation details of the YAML library and the
   * provided configuration data types.
   *
   * @tparam ConfigType The type of the new configuration data to be merged.
   * This type must be compatible with the YAML representation used by the
   * class, as the method internally converts the provided configuration data to
   * a YAML::Node.
   * @param newConfig The new configuration data to merge into the current
   * configuration. This data should ideally be a compatible subset or extension
   * of the existing configuration structure to ensure a smooth merge process.
   *
   * @throws YAML::Exception Thrown if the merging process encounters
   * YAML-specific errors, such as incompatible node types or invalid YAML
   * structures. When this exception is caught, the method falls back to
   * replacing the entire existing configuration with the newConfig. This
   * behavior is a safeguard against partial configuration updates that could
   * leave the configuration in an inconsistent state.
   * @throws std::runtime_error Thrown if any non-YAML related error occurs
   * during the update process. This includes errors related to internal
   * processing or other exceptional conditions not directly related to the
   * structure or content of the configuration data.
   *
   * Note: This method modifies the current configuration state and may result
   * in significant changes to the configuration structure. It is recommended to
   * perform validation checks on the new configuration data before invoking
   * this method to ensure compatibility and correctness of the resulting
   * configuration state.
   */
  template <typename ConfigType>
  void UpdateConfig(ConfigType newConfig) {
    try {
      // Implementation details here...
      MergeYAMLNodes(config, YAML::Node(newConfig));
    } catch (const YAML::Exception& e) {
      config = newConfig;
    } catch (...) {
      // Handle or rethrow all other exceptions
      throw std::runtime_error(
          "An error occurred while updating the configuration.");
    }
  }

  void SaveConfig() const { configManager->Save(); }

 private:
  std::shared_ptr<ConfigManager> configManager;
  YAML::Node config;

  void MergeYAMLNodes(YAML::Node currentConfig, const YAML::Node& newConfig);
};

}  // namespace nextgen::engine::configuration

#endif
