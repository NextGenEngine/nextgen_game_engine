#ifndef NEXTGEN_GAME_ENGINE_TEMPLATES_H
#define NEXTGEN_GAME_ENGINE_TEMPLATES_H

#include <concepts>

#include "components/configuration/config_manager.h"
#include "nextgen_game_engine_interfaces.h"

// NOLINTBEGIN(misc-non-private-member-variables-in-classes)
namespace nextgen::engine::templates {
using interfaces::IConfigurable;
using interfaces::IConfigurationStrategy;
using interfaces::IConfigValidator;

template <typename T, typename ConfigType>
concept ConfigValidator = requires(T typ, ConfigType config) {
  { typ.Validate(config) } -> std::same_as<bool>;
};

template <typename T>
concept ConfigurationStrategy = requires(T typ) {
  { typ.Configure() };
};

template <typename T>
concept Configurable = requires(T typ, const void* config) {
  { typ.ApplyConfiguration(config) };
};

template <typename ConfigType, ConfigValidator<ConfigType> ConfigValidator,
          ConfigurationStrategy PrimaryStrategy,
          ConfigurationStrategy DefaultStrategy,
          Configurable ConfigurableComponent>
struct FallbackConfigurationStrategyTemplate : public IConfigurationStrategy {
  configuration::ComponentConfig component_config_;
  ConfigValidator config_validator_;
  PrimaryStrategy primary_strategy_;
  DefaultStrategy default_strategy_;
  ConfigurableComponent configurable_component_;

  FallbackConfigurationStrategyTemplate() = default;

  void Configure() override {
    auto maybe_config = component_config_.LoadConfig<ConfigType>();
    if (maybe_config.has_value() &&
        config_validator_.Validate(maybe_config.value())) {
      // Configuration is valid, apply it
      ConfigType config = maybe_config.value();
      configurable_component_.ApplyConfiguration(&config);
    } else {
      // Fallback to default configuration if load fails or validation fails
      default_strategy_.Configure();
    }
  }
};

}  // namespace nextgen::engine::templates
// NOLINTEND(misc-non-private-member-variables-in-classes)

#endif
