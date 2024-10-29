#include "rendering_config_strategy_primary.h"

#include "components/configuration/config_repo.h"
#include "components/rendering/rendering_config.h"
#include "components/rendering/rendering_engine.h"
#include "rendering_config_sub_strategy_selector.h"
#include "rendering_config_validator.h"

namespace nextgen::engine::rendering {

using configuration::ConfigRepositoryNode;

RenderingConfigurationPrimaryStrategy::RenderingConfigurationPrimaryStrategy(
    ComponentConfig& component_config,
    RenderingConfigurationStrategySelector& api_strategy_selector,
    RenderingEngine& rendering_engine)
    : component_config_(component_config),
      api_strategy_selector_(api_strategy_selector),
      rendering_engine_(rendering_engine) {}

bool RenderingConfigurationPrimaryStrategy::Configure() {
  auto rendering_engine_config_opt =
      component_config_.LoadConfig<RenderingEngineConfig>();

  if (!rendering_engine_config_opt ||
      !RenderingConfigValidator::Validate(*rendering_engine_config_opt)) {
    return false;
  }

  auto rendering_engine_config = rendering_engine_config_opt.value();

  // Configure sub components (Vulkan/DirectX rendering api) first, and only
  // then apply configuration to root component
  api_strategy_selector_.SelectAndConfigure(rendering_engine_config.api);
  rendering_engine_.ApplyConfiguration(rendering_engine_config);
  return true;
}

}  // namespace nextgen::engine::rendering
