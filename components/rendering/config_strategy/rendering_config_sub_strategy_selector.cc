#include "rendering_config_sub_strategy_selector.h"

#include <stdexcept>

#include "components/rendering/rendering_config.h"
#include "components/rendering/rendering_engine.h"

namespace nextgen::engine::rendering {

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
