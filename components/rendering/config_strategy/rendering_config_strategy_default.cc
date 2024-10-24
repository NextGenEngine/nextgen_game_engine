#include "rendering_config_strategy_default.h"

#include "components/configuration/config_manager.h"
#include "components/rendering/rendering_config.h"
#include "components/rendering/rendering_engine.h"
#include "rendering_config_sub_strategy_selector.h"
#include "rendering_config_validator.h"

namespace nextgen::engine::rendering {

using configuration::ComponentConfig;

auto DefaultConfig = []() -> RenderingEngineConfig {
  return RenderingEngineConfig{.api = RenderingAPIEnum::Vulkan};
};

bool RenderingConfigurationDefaultStrategy::Configure() {
  auto rendering_engine_config = DefaultConfig();

  if (!RenderingConfigValidator::Validate(rendering_engine_config)) {
    return false;
  }

  component_config_->UpdateConfig(rendering_engine_config);
  component_config_->SaveConfig();
  rendering_engine_->ApplyConfiguration(&rendering_engine_config);

  auto* sub_component_strategy =
      api_strategy_selector_->SelectStrategy(rendering_engine_config.api);
  return sub_component_strategy->Configure();
}

void RenderingConfigurationDefaultStrategy::Initialize(
    ComponentConfig component_config, RenderingEngine& rendering_engine,
    RenderingConfigurationStrategySelector& api_strategy_selector) {
  rendering_engine_ = &rendering_engine;
  component_config_ = &component_config;
  api_strategy_selector_ = &api_strategy_selector;

  InitializeSubStrategies(*component_config_, *api_strategy_selector_,
                          *rendering_engine_);
}

}  // namespace nextgen::engine::rendering
