#include "config_orchestrator.h"

#include "components/configuration/repository/config_repo.h"
#include "components/rendering/api/vulkan/vulkan_config.h"
#include "components/rendering/rendering_config.h"
#include "components/rendering/rendering_engine.h"

namespace {

using nextgen::engine::configuration::ConfigRepository;
using nextgen::engine::configuration::ConfigRepositoryNode;
using nextgen::engine::rendering::RenderingEngine;
using nextgen::engine::rendering::RenderingEngineConfig;
using nextgen::engine::rendering::vulkan::VulkanConfig;

template <typename ConfigType>
auto LoadConfig(const ConfigRepositoryNode& config_node) {
  return config_node.LoadConfig<ConfigType>();
};

auto LoadRenderingConfig(ConfigRepository& config_repo) {
  return LoadConfig<RenderingEngineConfig>(config_repo["rendering"]);
};

auto LoadVulkanConfig(ConfigRepository& config_repo) {
  return LoadConfig<VulkanConfig>(config_repo["rendering"]["vulkan"]);
};

}  // namespace

namespace nextgen::engine::configuration {

ConfigOrchestrator::ConfigOrchestrator(ConfigRepository& config_repo,
                                       RenderingEngine& rendering_engine,
                                       VulkanRenderingApi& vulkan_rendering_api)
    : rendering_config_manager_(rendering_engine,
                                LoadRenderingConfig(config_repo)),
      vulkan_config_manager_(vulkan_rendering_api,
                             LoadVulkanConfig(config_repo)) {}

void ConfigOrchestrator::Configure() {
  vulkan_config_manager_.ConfigureComponent();
  rendering_config_manager_.ConfigureComponent();
}

}  // namespace nextgen::engine::configuration
