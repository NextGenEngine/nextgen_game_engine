#include "config_orchestrator.h"

#include <optional>

#include "components/configuration/managers/config_manager_template.h"
#include "components/configuration/repository/config_repo.h"
#include "components/rendering/api/vulkan/vulkan_config.h"
#include "components/rendering/api/vulkan/vulkan_rendering.h"
#include "components/rendering/rendering_config.h"
#include "components/rendering/rendering_engine.h"

namespace {

using nextgen::engine::configuration::ConfigRepository;
using nextgen::engine::configuration::ConfigRepositoryNode;
using nextgen::engine::configuration::ConfigWithDefaultFlag;
using nextgen::engine::rendering::RenderingEngine;
using nextgen::engine::rendering::RenderingEngineConfig;
using nextgen::engine::rendering::vulkan::VulkanConfig;
using nextgen::engine::rendering::vulkan::VulkanRenderingApi;

template <typename ConfigType, typename EngineComponent>
auto LoadConfigWithDefault(ConfigRepositoryNode config_node,
                           EngineComponent& engine_component) {
  // Load the configuration or use the default if unavailable
  auto config_opt = config_node.LoadConfig<ConfigType>();

  // Use config_opt if available, validate it and apply corrections, otherwise
  // use default
  auto validated_config =
      config_opt ? engine_component.ValidateConfig(*config_opt) : std::nullopt;

  return ConfigWithDefaultFlag<ConfigType>{
      !validated_config.has_value(),
      validated_config.value_or(engine_component.GetDefaultConfig())};
}

auto LoadRenderingConfig(ConfigRepository& config_manager,
                         RenderingEngine& rendering_engine) {
  return LoadConfigWithDefault<RenderingEngineConfig>(
      config_manager["rendering"], rendering_engine);
};

auto LoadVulkanConfig(ConfigRepository& config_manager,
                      VulkanRenderingApi& vulkan_api) {
  return LoadConfigWithDefault<VulkanConfig>(
      config_manager["rendering"]["vulkan"], vulkan_api);
};

}  // namespace

namespace nextgen::engine::configuration {

ConfigOrchestrator::ConfigOrchestrator(
    ConfigRepository& config_manager,
    rendering::RenderingEngine& rendering_engine)
    : rendering_config_manager_(
          rendering_engine,
          LoadRenderingConfig(config_manager, rendering_engine)),
      vulkan_config_manager_(
          rendering_engine.apis_.vulkan_rendering_api,
          LoadVulkanConfig(config_manager,
                           rendering_engine.apis_.vulkan_rendering_api)) {}

void ConfigOrchestrator::Configure() {
  vulkan_config_manager_.ConfigureComponent();
  rendering_config_manager_.ConfigureComponent();
}

}  // namespace nextgen::engine::configuration
