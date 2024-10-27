#ifndef NEXTGEN_ENGINE_RENDERING_H
#define NEXTGEN_ENGINE_RENDERING_H

#include "components/configuration/config_manager.h"
#include "components/engine/nextgen_game_engine_interfaces.h"
#include "components/rendering/api/vulkan/vulkan_rendering.h"
#include "components/rendering/rendering_api.h"
#include "components/rendering/rendering_config.h"

namespace nextgen::engine::rendering {

using interfaces::IConfigurable;
using interfaces::IConfigurationStrategy;
using nextgen::engine::configuration::ComponentConfig;
using nextgen::engine::rendering::api::IRenderingApi;

struct RenderingEngineData {
  RenderingEngineConfig rendering_engine_config_{};
  IRenderingApi* api_{};
  struct {
    vulkan::VulkanRenderingApi vulkan_rendering_api;
    // directx::DirectXRenderingApi directx_rendering_api;
  } apis_;
};

struct RenderingEngine : RenderingEngineData,
                         IConfigurable<RenderingEngineConfig> {
  explicit RenderingEngine();
  void Shutdown();
  void ApplyConfiguration(const RenderingEngineConfig& config) override;
  void MainLoop();

 private:
  IRenderingApi* GetRenderingApiInstance(RenderingAPIEnum newApi);
  void SwitchRenderingApi(RenderingAPIEnum newApi);
  void Render();
  bool Exiting();
};

}  // namespace nextgen::engine::rendering

#endif
