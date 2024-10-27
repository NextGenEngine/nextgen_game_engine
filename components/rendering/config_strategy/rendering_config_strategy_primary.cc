#include "rendering_config_strategy_primary.h"

#include "components/configuration/config_manager.h"
#include "components/rendering/rendering_config.h"
#include "components/rendering/rendering_engine.h"
#include "rendering_config_sub_strategy_selector.h"
#include "rendering_config_validator.h"

namespace nextgen::engine::rendering {

using configuration::ComponentConfig;

RenderingConfigurationPrimaryStrategy::RenderingConfigurationPrimaryStrategy(
    ComponentConfig& component_config,
    RenderingConfigurationStrategySelector& api_strategy_selector,
    RenderingEngine& rendering_engine)
    : component_config_(component_config),
      api_strategy_selector_(api_strategy_selector),
      rendering_engine_(rendering_engine) {}

bool RenderingConfigurationPrimaryStrategy::Configure() {
  auto rendering_engine_config =
      component_config_.LoadConfig<RenderingEngineConfig>();

  if (!rendering_engine_config) {
    return false;
  }

  if (!RenderingConfigValidator::Validate(*rendering_engine_config)) {
    return false;
  }

  rendering_engine_.ApplyConfiguration(*rendering_engine_config);

  auto* strategy =
      api_strategy_selector_.SelectStrategy(rendering_engine_config->api);
  return strategy->Configure();
}

}  // namespace nextgen::engine::rendering
