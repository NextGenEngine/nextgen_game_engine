#ifndef NEXTGEN_ENGINE_RENDERING_CONFIG_VALIDATOR_H
#define NEXTGEN_ENGINE_RENDERING_CONFIG_VALIDATOR_H

#include "components/rendering/rendering_config.h"

namespace nextgen::engine::rendering {

struct RenderingConfigValidator {
  static bool Validate(RenderingEngineConfig config);
};

}  // namespace nextgen::engine::rendering

#endif
