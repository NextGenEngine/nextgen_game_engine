#include "rendering_engine.h"

#include <cassert>
#include <cctype>
#include <iostream>
#include <optional>
#include <stdexcept>

#include "components/rendering/rendering_config.h"

namespace nextgen::engine::rendering {

RenderingEngine::RenderingEngine() {
  std::cout << "Rendering engine object created\n";
}

void RenderingEngine::ApplyConfiguration(const RenderingEngineConfig& config) {
  if (rendering_engine_config_.api != config.api || api_ == nullptr) {
    SwitchRenderingApi(config.api);
  }
  rendering_engine_config_ = config;
}

void RenderingEngine::Shutdown() {
  if (api_ == nullptr) {
    return;
  }
  api_->Shutdown();
}

void RenderingEngine::MainLoop() {
  if (api_ == nullptr) {
    throw std::runtime_error(
        "RenderingEngine: FATAL ERROR. Rendering engine API was not "
        "initialized");
  }
  api_->MainLoop();
}

void RenderingEngine::Render() {
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

RenderingEngineConfig RenderingEngine::GetDefaultConfig() {
  return RenderingEngineConfig{.api = RenderingAPIEnum::Vulkan};
}

std::optional<RenderingEngineConfig> RenderingEngine::ValidateConfig(
    const RenderingEngineConfig& config) {
  switch (config.api) {
    case RenderingAPIEnum::Vulkan:
    case RenderingAPIEnum::OpenGL:
    case RenderingAPIEnum::DirectX:
      break;
    default:
      return std::nullopt;
  }
  return std::make_optional(config);
}

}  // namespace nextgen::engine::rendering
