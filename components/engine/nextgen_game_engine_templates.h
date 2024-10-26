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

template <ConfigurationStrategy PrimaryStrategy,
          ConfigurationStrategy DefaultStrategy, typename ConfigurableComponent>
struct FallbackConfigurationStrategyTemplate : public IConfigurationStrategy {
  configuration::ComponentConfig component_config_;
  PrimaryStrategy primary_strategy_;
  DefaultStrategy default_strategy_;

  FallbackConfigurationStrategyTemplate(
      configuration::ComponentConfig component_config,
      ConfigurableComponent& configurable_component)
      : component_config_(component_config),
        primary_strategy_(component_config_, configurable_component),
        default_strategy_(component_config_, configurable_component) {}

  bool Configure() override {
    if (primary_strategy_.Configure()) {
      return true;
    }
    // Fallback to default configuration if load fails or validation fails
    return default_strategy_.Configure();
  }
};

}  // namespace nextgen::engine::templates
// NOLINTEND(misc-non-private-member-variables-in-classes)

#endif
