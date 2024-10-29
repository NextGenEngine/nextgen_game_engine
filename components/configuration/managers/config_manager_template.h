#ifndef NEXTGEN_ENGINE_CONFIGURATION_CONFIG_COMPONENT_MANAGER_H
#define NEXTGEN_ENGINE_CONFIGURATION_CONFIG_COMPONENT_MANAGER_H

#include <optional>
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

template <typename ConfigType, typename EngineComponent>
auto LoadConfigOrDefault(std::optional<ConfigType> config_opt,
                         EngineComponent& engine_component) {
  // Use config_opt if available, validate it and apply corrections, otherwise
  // use default
  auto validated_config =
      config_opt ? engine_component.ValidateConfig(*config_opt) : std::nullopt;

  return ConfigWithDefaultFlag<ConfigType>{
      !validated_config.has_value(),
      validated_config.value_or(engine_component.GetDefaultConfig())};
}

template <typename ComponentType, typename ConfigType>
struct ConfigComponentManager {
  explicit ConfigComponentManager(ComponentType& component,
                                  std::optional<ConfigType> config)
      : component_(component),
        config_wrapper_(
            std::move(LoadConfigOrDefault<ConfigType, ComponentType>(
                std::move(config), component))) {}

  // Returns an immutable ref of the component's configuration wrapper
  const ConfigWithDefaultFlag<ConfigType>& GetConfigWrapperRef() const {
    return config_wrapper_;
  }
  // Returns an mutable ref of the component's configuration wrapper
  ConfigWithDefaultFlag<ConfigType>& GetConfigWrapperMutableRef() {
    return config_wrapper_;
  }
  // Returns a copy of the component's configuration wrapper
  ConfigWithDefaultFlag<ConfigType> GetConfigWrapperCopy() const {
    return config_wrapper_;
  }

  // Returns an immutable ref of the component's configuration
  const ConfigType& GetConfigRef() const { return config_wrapper_.config; }
  // Returns an mutable ref of the component's configuration
  ConfigType& GetConfigMutableRef() { return config_wrapper_.config; }
  // Returns a copy of the component's configuration
  ConfigType GetConfigCopy() const { return config_wrapper_.config; }

  // Saves configuration locally and marks, that it is not default anymore
  void SetConfiguration(const ConfigType& config) {
    // using __builtin_expect as hint to the compiler to optimize the code
    // layout accordingly
    if (__builtin_expect(component_.ValidateConfig(config), 1)) {
      config_wrapper_.config = config;  // Update the local copy
      config_wrapper_.is_default = false;
      modified = true;
    }
  }

  void ConfigureComponent() {
    if (!modified) {
      return;
    }
    component_.ApplyConfiguration(config_wrapper_.config);
    modified = false;
  }

 protected:
  ComponentType& component_;
  ConfigWithDefaultFlag<ConfigType> config_wrapper_;
  bool modified{true};
};

}  // namespace nextgen::engine::configuration
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)

#endif
