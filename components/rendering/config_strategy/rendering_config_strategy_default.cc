#include "rendering_config_strategy_default.h"

#include "components/configuration/config_repo.h"
#include "components/rendering/rendering_config.h"
#include "components/rendering/rendering_engine.h"
#include "rendering_config_sub_strategy_selector.h"
#include "rendering_config_validator.h"

namespace {
using nextgen::engine::rendering::RenderingAPIEnum;
using nextgen::engine::rendering::RenderingEngineConfig;

auto DefaultConfig = []() -> RenderingEngineConfig {
  return RenderingEngineConfig{.api = RenderingAPIEnum::Vulkan};
};

}  // namespace

namespace nextgen::engine::rendering {

using configuration::ConfigRepositoryNode;

RenderingConfigurationDefaultStrategy::RenderingConfigurationDefaultStrategy(
    ComponentConfig& component_config,
    RenderingConfigurationStrategySelector& api_strategy_selector,
    RenderingEngine& rendering_engine)
    : component_config_(component_config),
      api_strategy_selector_(api_strategy_selector),
      rendering_engine_(rendering_engine) {}

bool RenderingConfigurationDefaultStrategy::Configure() {
  auto rendering_engine_config = DefaultConfig();

  if (!RenderingConfigValidator::Validate(rendering_engine_config)) {
    return false;
  }

  component_config_.UpdateConfig(rendering_engine_config);
  component_config_.Save();

  // Configure sub components (Vulkan/DirectX rendering api) first, and only
  // then apply configuration to root component
  api_strategy_selector_.SelectAndConfigure(rendering_engine_config.api);
  rendering_engine_.ApplyConfiguration(rendering_engine_config);
  return true;
}

}  // namespace nextgen::engine::rendering
