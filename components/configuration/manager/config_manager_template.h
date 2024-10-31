#ifndef NEXTGEN_ENGINE_CONFIGURATION_CONFIG_COMPONENT_MANAGER_H
#define NEXTGEN_ENGINE_CONFIGURATION_CONFIG_COMPONENT_MANAGER_H

#include <optional>
#include <utility>

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)

namespace nextgen::engine::configuration {

template <typename EngineComponentType>
concept EngineComponentTypeConcept = requires(
    EngineComponentType component,
    typename EngineComponentType::ConfigType config) {
  {
    component.GetDefaultConfig()
  } -> std::same_as<typename EngineComponentType::ConfigType>;
  {
    component.ValidateConfig(config)
  } -> std::same_as<std::optional<typename EngineComponentType::ConfigType>>;
  { component.ApplyConfiguration(config) } -> std::same_as<void>;
};

template <typename ConfigType>
struct TConfigWithDefaultFlag {
  bool is_default;
  ConfigType config;

  TConfigWithDefaultFlag(bool is_default, ConfigType config)
      : is_default(is_default), config(std::move(config)) {}
};

template <typename ConfigType, typename EngineComponentType>
auto LoadConfigOrDefault(std::optional<ConfigType> config_opt,
                         EngineComponentType& engine_component) {
  // Use config_opt if available, validate it and apply corrections, otherwise
  // use default
  auto validated_config =
      config_opt ? engine_component.ValidateConfig(*config_opt) : std::nullopt;

  return TConfigWithDefaultFlag<ConfigType>{
      !validated_config.has_value(), validated_config
                                         ? *validated_config
                                         : engine_component.GetDefaultConfig()};
}

template <typename EngineComponentType>
  requires EngineComponentTypeConcept<EngineComponentType>
struct TConfigComponentManager {
  using ConfigType = typename EngineComponentType::ConfigType;
  explicit TConfigComponentManager(EngineComponentType& component,
                                   std::optional<ConfigType> config)
      : component_(component),
        config_wrapper_(
            std::move(LoadConfigOrDefault<ConfigType, EngineComponentType>(
                std::move(config), component))) {}

  // Returns an immutable ref of the component's configuration wrapper
  const TConfigWithDefaultFlag<ConfigType>& GetConfigWrapperRef() const {
    return config_wrapper_;
  }
  // Returns a copy of the component's configuration wrapper
  TConfigWithDefaultFlag<ConfigType> GetConfigWrapperCopy() const {
    return config_wrapper_;
  }

  // Returns an immutable ref of the component's configuration
  const ConfigType& GetConfigRef() const { return config_wrapper_.config; }
  // Returns a copy of the component's configuration
  ConfigType GetConfigCopy() const { return config_wrapper_.config; }

  // Saves configuration locally and marks, that it is not default anymore
  TConfigWithDefaultFlag<ConfigType> SetConfiguration(
      const ConfigType& config) {
    auto validated_config = component_.ValidateConfig(config);
    // using __builtin_expect as hint to the compiler to optimize the code
    // layout accordingly
    if (__builtin_expect(validated_config.has_value(), 1)) {
      config_wrapper_.config =
          validated_config.value();  // Update the local copy
      config_wrapper_.is_default = false;
      modified = true;
    }
    return config_wrapper_;
  }

  void ConfigureComponent() {
    if (!modified) {
      return;
    }
    component_.ApplyConfiguration(config_wrapper_.config);
    modified = false;
  }

 protected:
  EngineComponentType& component_;
  TConfigWithDefaultFlag<ConfigType> config_wrapper_;
  bool modified{true};
};

}  // namespace nextgen::engine::configuration
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)

#endif
