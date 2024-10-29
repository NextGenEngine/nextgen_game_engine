#ifndef NEXTGEN_ENGINE_CONFIGURATION_CONFIG_COMPONENT_MANAGER_H
#define NEXTGEN_ENGINE_CONFIGURATION_CONFIG_COMPONENT_MANAGER_H

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)
namespace nextgen::engine::configuration {

template <typename ComponentType, typename ConfigType>
class ConfigComponentManager {
 public:
  explicit ConfigComponentManager(ComponentType& component, ConfigType config)
      : component_(component), config_(config) {}

  // Returns a copy of the component's configuration
  const ConfigType& GetConfigurationRef() const { return config_; }
  ConfigType& GetConfigurationMutableRef() { return config_; }
  ConfigType GetConfigurationCopy() const { return config_; }

  // Applies a new configuration to the component
  void SetConfiguration(const ConfigType& config) {
    config_ = config;  // Update the local copy
  }

  void ConfigureComponent() { component_.ApplyConfiguration(config_); }

 protected:
  ComponentType& component_;
  ConfigType config_;
};

}  // namespace nextgen::engine::configuration
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)

#endif
