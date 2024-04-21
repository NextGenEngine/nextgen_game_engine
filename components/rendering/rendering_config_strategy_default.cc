#include "components/rendering/rendering_config_strategy_default.h"

#include "components/configuration/config_manager.h"
#include "components/rendering/rendering.h"
#include "components/rendering/rendering_config.h"
#include "components/rendering/rendering_config_sub_strategy_selector.h"

namespace nextgen::engine::rendering {

using configuration::ComponentConfig;

auto DefaultConfig = []() -> RenderingEngineConfig {
  return RenderingEngineConfig{.api = RenderingAPIEnum::Vulkan};
};

bool RenderingConfigurationDefaultStrategy::Configure() {
  auto rendering_engine_config = DefaultConfig();
  component_config_.UpdateConfig(rendering_engine_config);
  component_config_.SaveConfig();
  rendering_engine_->ApplyConfiguration(&rendering_engine_config);

  auto* sub_component_strategy =
      api_strategy_selector_.SelectStrategy(rendering_engine_config.api);
  return sub_component_strategy->Configure();
}

void RenderingConfigurationDefaultStrategy::Initialize(
    ComponentConfig component_config, RenderingEngine& rendering_engine) {
  rendering_engine_ = &rendering_engine;
  component_config_ = component_config;

  InitializeSubStrategies(component_config_, api_strategy_selector_,
                          *rendering_engine_);
}

}  // namespace nextgen::engine::rendering
