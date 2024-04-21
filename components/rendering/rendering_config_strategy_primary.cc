#include "components/rendering/rendering_config_strategy_primary.h"

#include "components/configuration/config_manager.h"
#include "components/rendering/rendering.h"
#include "components/rendering/rendering_config.h"
#include "components/rendering/rendering_config_sub_strategy_selector.h"

namespace nextgen::engine::rendering {

using configuration::ComponentConfig;

bool RenderingConfigurationPrimaryStrategy::Configure() {
  auto rendering_engine_config =
      component_config_.LoadConfig<RenderingEngineConfig>();

  if (!rendering_engine_config) {
    return false;
  }

  rendering_engine_->ApplyConfiguration(&*rendering_engine_config);

  auto* strategy =
      api_strategy_selector_.SelectStrategy(rendering_engine_config->api);
  return strategy->Configure();
}

void RenderingConfigurationPrimaryStrategy::Initialize(
    ComponentConfig component_config, RenderingEngine& rendering_engine) {
  component_config_ = component_config;
  rendering_engine_ = &rendering_engine;

  auto vulkan_component_config = component_config_.getSubConfig("vulkan");
  api_strategy_selector_.vulkan_strategy_.Initialize(
      vulkan_component_config, rendering_engine.apis_.vulkan_rendering_api);
  InitializeSubStrategies(component_config_, api_strategy_selector_,
                          *rendering_engine_);
}

}  // namespace nextgen::engine::rendering
