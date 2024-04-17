#ifndef NEXTGEN_ENGINE_RENDERING_H
#define NEXTGEN_ENGINE_RENDERING_H

#include <iostream>

#include "components/configuration/config_manager.h"
#include "components/engine/nextgen_game_engine_interfaces.h"
#include "components/rendering/rendering_api.h"
#include "components/rendering/rendering_config.h"
#include "components/rendering/vulkan/vulkan_rendering.h"

namespace nextgen::engine::rendering {

using interfaces::IConfigurable;
using interfaces::IConfigurationStrategy;
using nextgen::engine::configuration::ComponentConfig;
using nextgen::engine::rendering::api::IRenderingApi;

// NOLINTBEGIN(misc-non-private-member-variables-in-classes)
struct RenderingEngine : public IConfigurable {
  RenderingEngineConfig rendering_engine_config_{};
  IRenderingApi* api_{};
  struct {
    vulkan::VulkanRenderingApi vulkan_rendering_api;
    // directx::DirectXRenderingApi directx_rendering_api;
  } apis_;

  explicit RenderingEngine() {
    std::cout << "Rendering engine object created\n";
  }

  void ApplyConfiguration(const void* config) override;

  void SwitchApi(RenderingAPIEnum newApi) {
    if (rendering_engine_config_.api == newApi && api_ != nullptr) {
      // NO CHANGE - NO ACTION
      return;
    }

    if (api_ != nullptr) {
      api_->Shutdown();
    }

    switch (newApi) {
      case RenderingAPIEnum::Vulkan:
        api_ = &apis_.vulkan_rendering_api;
        break;
      case RenderingAPIEnum::DirectX:
        throw std::runtime_error("Haha. DirectX is unsupported API");
      default:
        throw std::runtime_error("Unsupported API");
    }

    api_->Initialize();
  }

  void Initialize() {
    auto& vulkan_api = apis_.vulkan_rendering_api;
    vulkan_api.vulkan_instance_.vulkan_context_ =
        &vulkan_api.get_vulkan_context_ref();
    vulkan_api.m_vulkan_device.m_vulkan_context =
        &vulkan_api.get_vulkan_context_ref();
    vulkan_api.m_vulkan_device.m_vulkan_config =
        &vulkan_api.get_vulkan_config_ref();
    vulkan_api.m_vulkan_swap_chain.m_vulkanContext =
        &vulkan_api.get_vulkan_context_ref();
    vulkan_api.get_vulkan_context_ref() = {};
    vulkan_api.get_vulkan_config_ref() = {};
  }

  void render();
};
// NOLINTEND(misc-non-private-member-variables-in-classes)

}  // namespace nextgen::engine::rendering

#endif
