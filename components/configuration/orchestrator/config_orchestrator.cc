#include "config_orchestrator.h"

#include "components/configuration/repository/config_repo.h"
#include "components/rendering/api/vulkan/vulkan_config.h"
#include "components/rendering/rendering_config.h"
#include "components/rendering/rendering_engine.h"

namespace {
auto LoadRenderingConfig =
    [](nextgen::engine::configuration::ConfigRepository& config_manager)
    -> nextgen::engine::rendering::RenderingEngineConfig {
  return config_manager["rendering"]
      .LoadConfig<nextgen::engine::rendering::RenderingEngineConfig>()
      .value();
};

auto LoadVulkanConfig =
    [](nextgen::engine::configuration::ConfigRepository& config_manager)
    -> nextgen::engine::rendering::vulkan::VulkanConfig {
  return config_manager["rendering"]["vulkan"]
      .LoadConfig<nextgen::engine::rendering::vulkan::VulkanConfig>()
      .value();
};
}  // namespace

namespace nextgen::engine::configuration {

ConfigOrchestrator::ConfigOrchestrator(
    ConfigRepository& config_manager,
    rendering::RenderingEngine& rendering_engine)
    : rendering_config_manager_(rendering_engine,
                                LoadRenderingConfig(config_manager)),
      vulkan_config_manager_(rendering_engine.apis_.vulkan_rendering_api,
                             LoadVulkanConfig(config_manager)) {}

void ConfigOrchestrator::Configure() {
  vulkan_config_manager_.ConfigureComponent();
  rendering_config_manager_.ConfigureComponent();
}

}  // namespace nextgen::engine::configuration
