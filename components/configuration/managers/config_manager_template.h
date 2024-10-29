#ifndef NEXTGEN_ENGINE_CONFIGURATION_CONFIG_COMPONENT_MANAGER_H
#define NEXTGEN_ENGINE_CONFIGURATION_CONFIG_COMPONENT_MANAGER_H

#include <utility>

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)

namespace nextgen::engine::configuration {

template <typename ConfigType>
struct ConfigWithDefaultFlag {
  bool is_default;
  ConfigType config;

  ConfigWithDefaultFlag(bool is_default, ConfigType config)
      : is_default(is_default), config(std::move(config)) {}
};

template <typename ComponentType, typename ConfigType>
class ConfigComponentManager {
 public:
  explicit ConfigComponentManager(ComponentType& component,
                                  ConfigWithDefaultFlag<ConfigType> config)
      : component_(component), config_wrapper_(config) {}

  // Returns a copy of the component's configuration
  const ConfigType& GetConfigurationRef() const { return config_wrapper_; }
  ConfigType& GetConfigurationMutableRef() { return config_wrapper_; }
  ConfigType GetConfigurationCopy() const { return config_wrapper_; }

  // Saves configuration locally and marks, that it is not default anymore
  void SetConfiguration(const ConfigType& config) {
    config_wrapper_.config = config;  // Update the local copy
    config_wrapper_.is_default = false;
  }

  void ConfigureComponent() {
    component_.ApplyConfiguration(config_wrapper_.config);
  }

 protected:
  ComponentType& component_;
  ConfigWithDefaultFlag<ConfigType> config_wrapper_;
};

}  // namespace nextgen::engine::configuration
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)

#endif
