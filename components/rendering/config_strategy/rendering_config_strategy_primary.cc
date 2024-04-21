#include "rendering_config_strategy_primary.h"

#include "components/configuration/config_manager.h"
#include "components/rendering/rendering.h"
#include "components/rendering/rendering_config.h"
#include "rendering_config_sub_strategy_selector.h"
#include "rendering_config_validator.h"

namespace nextgen::engine::rendering {

using configuration::ComponentConfig;

bool RenderingConfigurationPrimaryStrategy::Configure() {
  auto rendering_engine_config =
      component_config_->LoadConfig<RenderingEngineConfig>();

  if (!rendering_engine_config) {
    return false;
  }

  if (!RenderingConfigValidator::Validate(*rendering_engine_config)) {
    return false;
  }

  rendering_engine_->ApplyConfiguration(&*rendering_engine_config);

  auto* strategy =
      api_strategy_selector_->SelectStrategy(rendering_engine_config->api);
  return strategy->Configure();
}

void RenderingConfigurationPrimaryStrategy::Initialize(
    ComponentConfig& component_config, RenderingEngine& rendering_engine,
    RenderingConfigurationStrategySelector& api_strategy_selector) {
  component_config_ = &component_config;
  rendering_engine_ = &rendering_engine;
  api_strategy_selector_ = &api_strategy_selector;

  InitializeSubStrategies(*component_config_, *api_strategy_selector_,
                          *rendering_engine_);
}

}  // namespace nextgen::engine::rendering
