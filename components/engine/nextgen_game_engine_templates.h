#ifndef NEXTGEN_GAME_ENGINE_TEMPLATES_H
#define NEXTGEN_GAME_ENGINE_TEMPLATES_H

#include <concepts>

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
          ConfigurationStrategy DefaultStrategy>
struct FallbackConfigurationStrategyTemplate : public IConfigurationStrategy {
  PrimaryStrategy primary_strategy_;
  DefaultStrategy default_strategy_;

  FallbackConfigurationStrategyTemplate() = default;

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
