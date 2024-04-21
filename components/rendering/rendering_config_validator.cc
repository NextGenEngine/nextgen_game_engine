#include "components/rendering/rendering_config_validator.h"

#include "components/rendering/rendering_config.h"

namespace nextgen::engine::rendering {

bool RenderingConfigValidator::Validate(RenderingEngineConfig config) {
  switch (config.api) {
    case RenderingAPIEnum::Vulkan:
    case RenderingAPIEnum::OpenGL:
    case RenderingAPIEnum::DirectX:
      break;
    default:
      return false;
  }
  return true;
}

}  // namespace nextgen::engine::rendering
