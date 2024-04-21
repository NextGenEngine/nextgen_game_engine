#include "components/rendering/rendering_config_strategy.h"

#include "components/configuration/config_manager.h"
#include "components/rendering/rendering.h"

namespace nextgen::engine::rendering {

using configuration::ComponentConfig;

void RenderingConfigurationStrategy::Initialize(
    ComponentConfig component_config, RenderingEngine& rendering_engine) {
  primary_strategy_.Initialize(component_config, rendering_engine);
  default_strategy_.Initialize(component_config, rendering_engine);
}

}  // namespace nextgen::engine::rendering