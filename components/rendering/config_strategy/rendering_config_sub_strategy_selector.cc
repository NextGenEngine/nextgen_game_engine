#include "rendering_config_sub_strategy_selector.h"

#include <stdexcept>

#include "components/rendering/rendering_config.h"
#include "components/rendering/rendering_engine.h"

namespace nextgen::engine::rendering {

RenderingConfigurationStrategySelector::RenderingConfigurationStrategySelector(
    ComponentConfig& component_config, RenderingEngine& rendering_engine)
    : vulkan_strategy_(component_config.GetComponentConfig("vulkan"),
                       rendering_engine),
      direct_x_strategy_(component_config) {}

IConfigurationStrategy* RenderingConfigurationStrategySelector::SelectStrategy(
    RenderingAPIEnum api) {
  switch (api) {
    case RenderingAPIEnum::Vulkan:
      return &vulkan_strategy_;
    case RenderingAPIEnum::DirectX:
      return &direct_x_strategy_;
    case RenderingAPIEnum::OpenGL:
      throw std::runtime_error("Haha. OpenGL is unsupported");
    default:
      throw std::runtime_error("Uhh... unknown rendering api");
  }
}

void RenderingConfigurationStrategySelector::SelectAndConfigure(
    RenderingAPIEnum api) {
  if (!SelectStrategy(api)->Configure()) {
    throw std::runtime_error(
        "RenderingConfigurationStrategySelector: FATAL ERROR. Cannot operate "
        "when sub components failed to configure");
  }
}

}  // namespace nextgen::engine::rendering
