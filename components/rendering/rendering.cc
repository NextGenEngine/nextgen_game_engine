#include "rendering.h"

#include <cctype>
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <thread>

#include "components/rendering/rendering_config.h"

namespace nextgen::engine::rendering {

void RenderingEngine::ApplyConfiguration(const void* config) {
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-cstyle-cast,google-readability-casting)
  const auto* new_config = (RenderingEngineConfig*)config;
  SwitchApi(new_config->api);
  rendering_engine_config_ = *new_config;
}

RenderingEngine::RenderingEngine() {
  std::cout << "Rendering engine object created\n";
}

void RenderingEngine::SwitchApi(RenderingAPIEnum newApi) {
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

void RenderingEngine::Initialize() {
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

void RenderingEngine::render() {
  std::this_thread::sleep_for(
      std::chrono::milliseconds(16));  // Simulate rendering time
}

}  // namespace nextgen::engine::rendering
