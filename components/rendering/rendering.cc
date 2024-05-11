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

  api_->StartUp();
}

void RenderingEngine::Initialize() {
  auto& vulkan_api = apis_.vulkan_rendering_api;
  vulkan_api.Initialize();
}

void RenderingEngine::Render() {
  if (api_ == nullptr) {
    return;
  }

  api_->Render();

  // std::this_thread::sleep_for(
  //     std::chrono::milliseconds(1000));  // Simulate rendering time
}

bool RenderingEngine::Exiting() {
  if (api_ == nullptr) {
    return true;
  }
  return api_->Exiting();
}

}  // namespace nextgen::engine::rendering
