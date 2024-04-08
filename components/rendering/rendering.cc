#include "rendering.h"

#include <cctype>
#include <memory>
#include <stdexcept>
#include <utility>

#include "components/configuration/config_manager.h"
#include "components/rendering/rendering_api.h"
#include "components/rendering/rendering_config.h"
#include "vulkan/vulkan_rendering.h"

namespace nextgen::engine::rendering {
using nextgen::engine::configuration::ComponentConfig;
using nextgen::engine::rendering::api::IRenderingApi;
using nextgen::engine::rendering::vulkan::VulkanRenderingApi;

IRenderingApi::~IRenderingApi() = default;

auto DefaultConfig = []() -> RenderingEngineConfig {
  return RenderingEngineConfig({});
};

inline std::unique_ptr<IRenderingApi> SelectRenderingApi(
    RenderingEngineConfig* config, ComponentConfig* componentConfig) {
  switch (config->api) {
    case RenderingAPI::Vulkan:
      return std::make_unique<VulkanRenderingApi>(
          componentConfig->getSubConfig("vulkan"));
    case RenderingAPI::DirectX:
      throw std::runtime_error("Ha-ha: no DirectX yet");
    default:
      config->api = RenderingAPI::Vulkan;
      (*componentConfig)() = *config;
      return std::make_unique<VulkanRenderingApi>(
          componentConfig->getSubConfig("vulkan"));
  }
}

auto inline LoadConfigOrDefault(ComponentConfig& componentConfig) {
  auto config = componentConfig.LoadConfig<RenderingEngineConfig>();
  if (config) {
    return config.value();
  }
  // If configuration was not loaded, than fall back to default one
  auto defaultConfig = DefaultConfig();
  componentConfig.UpdateConfig(defaultConfig);
  componentConfig.SaveConfig();
  return defaultConfig;
}

RenderingEngine::RenderingEngine(ComponentConfig _componentConfig)
    : componentConfig(std::move(_componentConfig)),
      config(LoadConfigOrDefault(componentConfig)),
      api(SelectRenderingApi(&config, &componentConfig)) {}

}  // namespace nextgen::engine::rendering
