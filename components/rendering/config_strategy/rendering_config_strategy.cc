#include "rendering_config_strategy.h"

#include "components/configuration/config_manager.h"
#include "components/rendering/rendering_engine.h"

namespace nextgen::engine::rendering {

using configuration::ComponentConfig;

RenderingConfigurationStrategy::RenderingConfigurationStrategy(
    ComponentConfig component_config, RenderingEngine& rendering_engine)
    : component_config_(component_config),
      api_strategy_selector_(component_config_, rendering_engine),
      primary_strategy_(component_config_, api_strategy_selector_,
                        rendering_engine),
      default_strategy_(component_config_, api_strategy_selector_,
                        rendering_engine) {}

bool RenderingConfigurationStrategy::Configure() {
  if (primary_strategy_.Configure()) {
    return true;
  }
  // Fallback to default configuration if load fails or validation fails
  return default_strategy_.Configure();
}

}  // namespace nextgen::engine::rendering
