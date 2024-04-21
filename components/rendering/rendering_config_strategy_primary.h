#ifndef NEXTGEN_ENGINE_RENDERING_CONFIG_STRATEGY_PRIMARY_H
#define NEXTGEN_ENGINE_RENDERING_CONFIG_STRATEGY_PRIMARY_H

#include "components/rendering/rendering.h"
#include "components/rendering/rendering_config_sub_strategy_selector.h"

namespace nextgen::engine::rendering {

struct RenderingConfigurationPrimaryStrategyData {
  ComponentConfig component_config_;
  RenderingConfigurationStrategySelector* api_strategy_selector_;
  RenderingEngine* rendering_engine_;
};
struct RenderingConfigurationPrimaryStrategy
    : RenderingConfigurationPrimaryStrategyData,
      IConfigurationStrategy {
  bool Configure() override;
  void Initialize(
      ComponentConfig component_config, RenderingEngine& rendering_engine,
      RenderingConfigurationStrategySelector& api_strategy_selector);
};

}  // namespace nextgen::engine::rendering

#endif
