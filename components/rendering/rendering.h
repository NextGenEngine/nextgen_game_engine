#ifndef NEXTGEN_ENGINE_RENDERING_H
#define NEXTGEN_ENGINE_RENDERING_H

#include "components/configuration/config_manager.h"
#include "components/rendering/rendering_api.h"
#include "components/rendering/rendering_config.h"

namespace nextgen::engine::rendering {

using nextgen::engine::configuration::ComponentConfig;
using nextgen::engine::rendering::api::IRenderingApi;

class RenderingEngine {
  configuration::ComponentConfig componentConfig;
  RenderingEngineConfig config;
  std::unique_ptr<IRenderingApi> api;

 public:
  explicit RenderingEngine(const ComponentConfig& _componentConfig);
};

}  // namespace nextgen::engine::rendering

#endif
