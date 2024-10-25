#include <cctype>
#include <stdexcept>

#include "components/rendering/rendering_config.h"
#include "rendering_engine.h"

namespace nextgen::engine::rendering {

IRenderingApi* RenderingEngine::GetRenderingApiInstance(
    const RenderingAPIEnum newApi) {
  switch (newApi) {
    case RenderingAPIEnum::Vulkan:
      return &apis_.vulkan_rendering_api;
    case RenderingAPIEnum::DirectX:
      throw std::runtime_error("Haha. DirectX is unsupported API");
    default:
      throw std::runtime_error("Unsupported API");
  }
}

void RenderingEngine::SwitchRenderingApi(const RenderingAPIEnum newApi) {
  if (api_ != nullptr) {
    api_->Shutdown();
  }
  api_ = GetRenderingApiInstance(newApi);
  api_->Initialize();
}

}  // namespace nextgen::engine::rendering
