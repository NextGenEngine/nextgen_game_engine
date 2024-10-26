#ifndef NEXTGEN_ENGINE_RENDERING_CONFIG_STRATEGY_DEFAULT_H
#define NEXTGEN_ENGINE_RENDERING_CONFIG_STRATEGY_DEFAULT_H

#include "components/rendering/rendering_engine.h"
#include "rendering_config_sub_strategy_selector.h"

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)
namespace nextgen::engine::rendering {

struct RenderingConfigurationDefaultStrategyData {
  ComponentConfig& component_config_;
  RenderingConfigurationStrategySelector api_strategy_selector_;
  RenderingEngine& rendering_engine_;
};
struct RenderingConfigurationDefaultStrategy
    : RenderingConfigurationDefaultStrategyData,
      IConfigurationStrategy {
  bool Configure() override;
  void Initialize(
      ComponentConfig component_config, RenderingEngine& rendering_engine,
      RenderingConfigurationStrategySelector& api_strategy_selector);

  RenderingConfigurationDefaultStrategy(
      ComponentConfig& component_config,
      RenderingConfigurationStrategySelector& api_strategy_selector,
      RenderingEngine& rendering_engine)
      : RenderingConfigurationDefaultStrategyData(
            component_config, api_strategy_selector, rendering_engine) {}
};

}  // namespace nextgen::engine::rendering
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)

#endif
