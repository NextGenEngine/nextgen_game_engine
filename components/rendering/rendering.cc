#include "rendering.h"

#include <cctype>
#include <memory>
#include <stdexcept>
#include <thread>
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
  return RenderingEngineConfig({.api = RenderingAPI::Vulkan});
};

auto UpdateComponentConfigDefault(ComponentConfig* component_config) {
  auto default_config = DefaultConfig();
  component_config->UpdateConfig(default_config);
  component_config->SaveConfig();
  return default_config;
}

std::unique_ptr<IRenderingApi> SelectRenderingApi(
    RenderingEngineConfig* config, ComponentConfig* componentConfig) {
  switch (config->api) {
    case RenderingAPI::Vulkan:
      return std::make_unique<VulkanRenderingApi>(
          componentConfig->getSubConfig("vulkan"));
    case RenderingAPI::DirectX:
      throw std::runtime_error("Ha-ha: no DirectX yet");
    default:
      UpdateComponentConfigDefault(componentConfig);
      return std::make_unique<VulkanRenderingApi>(
          componentConfig->getSubConfig("vulkan"));
  }
}

auto LoadConfigOrDefault(ComponentConfig& component_config) {
  auto config = component_config.LoadConfig<RenderingEngineConfig>();
  if (config) {
    return config.value();
  }
  // If configuration was not loaded, than fall back to default one
  return UpdateComponentConfigDefault(&component_config);
}

RenderingEngine::RenderingEngine(ComponentConfig component_config)
    : m_component_config(std::move(component_config)),
      m_config(LoadConfigOrDefault(m_component_config)),
      m_api(SelectRenderingApi(&m_config, &m_component_config)) {}

void RenderingEngine::render() {
  std::this_thread::sleep_for(
      std::chrono::milliseconds(16));  // Simulate rendering time
}

}  // namespace nextgen::engine::rendering
