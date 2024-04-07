#include "rendering.h"

#include <algorithm>
#include <cctype>
#include <memory>
#include <stdexcept>
#include <utility>

#include "components/configuration/config_manager.h"
#include "components/rendering/rendering_api.h"
#include "components/rendering/rendering_config.h"
#include "vulkan/vulkan_rendering.h"

using nextgen::engine::configuration::ComponentConfig;
using nextgen::engine::rendering::RenderingAPI;
using nextgen::engine::rendering::RenderingEngine;
using nextgen::engine::rendering::RenderingEngineConfig;
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

RenderingEngine::RenderingEngine(ComponentConfig _componentConfig)
    : componentConfig(std::move(_componentConfig)),
      config(componentConfig.LoadConfigOrDefault<RenderingEngineConfig>(
          DefaultConfig)),
      api(SelectRenderingApi(&config, &componentConfig)) {}

std::string toLowerCase(const std::string& input) {
  std::string output = input;
  std::transform(output.begin(), output.end(), output.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  return output;
}
