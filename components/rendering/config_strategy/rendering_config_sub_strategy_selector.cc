#include "rendering_config_sub_strategy_selector.h"

#include <stdexcept>

#include "components/rendering/rendering.h"
#include "components/rendering/rendering_config.h"

namespace nextgen::engine::rendering {

void InitializeSubStrategies(ComponentConfig& component_config,
                             RenderingConfigurationStrategySelector& selector,
                             RenderingEngine& rendering_engine) {
  auto vulkan_component_config = component_config.getSubConfig("vulkan");
  selector.vulkan_strategy_.Initialize(
      vulkan_component_config, rendering_engine.apis_.vulkan_rendering_api);
}

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

}  // namespace nextgen::engine::rendering
