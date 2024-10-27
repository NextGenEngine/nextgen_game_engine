#ifndef NEXTGEN_ENGINE_RENDERING_CONFIG_STRATEGY_PRIMARY_H
#define NEXTGEN_ENGINE_RENDERING_CONFIG_STRATEGY_PRIMARY_H

#include "components/rendering/rendering_engine.h"
#include "rendering_config_sub_strategy_selector.h"

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)
namespace nextgen::engine::rendering {

struct RenderingConfigurationPrimaryStrategy : IConfigurationStrategy {
  RenderingConfigurationPrimaryStrategy(
      ComponentConfig& component_config,
      RenderingConfigurationStrategySelector& api_strategy_selector,
      RenderingEngine& rendering_engine);

  bool Configure() override;

  ComponentConfig& component_config_;
  RenderingConfigurationStrategySelector& api_strategy_selector_;
  RenderingEngine& rendering_engine_;
};

}  // namespace nextgen::engine::rendering
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)

#endif
