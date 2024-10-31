#ifndef NEXTGEN_ENGINE_RENDERING_H
#define NEXTGEN_ENGINE_RENDERING_H

#include <optional>

#include "components/configuration/repository/config_repo.h"
#include "components/rendering/api/vulkan/vulkan_rendering.h"
#include "components/rendering/rendering_api.h"
#include "components/rendering/rendering_config.h"

namespace nextgen::engine::rendering {

using nextgen::engine::configuration::ConfigRepositoryNode;
using nextgen::engine::rendering::api::IRenderingApi;

struct RenderingEngineData {
  RenderingEngineConfig rendering_engine_config_{};
  IRenderingApi* api_{};
  struct {
    vulkan::VulkanRenderingApi vulkan_rendering_api;
    // directx::DirectXRenderingApi directx_rendering_api;
  } apis_;
};

struct RenderingEngine : RenderingEngineData {
  // this one is required for type erasure in templated components
  using ConfigType = RenderingEngineConfig;

  explicit RenderingEngine();
  void Shutdown();
  void ApplyConfiguration(const RenderingEngineConfig& config);
  void MainLoop();
  static RenderingEngineConfig GetDefaultConfig();
  static std::optional<RenderingEngineConfig> ValidateConfig(
      const RenderingEngineConfig& config);

 private:
  IRenderingApi* GetRenderingApiInstance(RenderingAPIEnum newApi);
  void SwitchRenderingApi(RenderingAPIEnum newApi);
  void Render();
  bool Exiting();
};

}  // namespace nextgen::engine::rendering

#endif
