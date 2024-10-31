#ifndef NEXTGEN_ENGINE_CONFIGURATION_CONFIG_ORCHESTRATOR_H
#define NEXTGEN_ENGINE_CONFIGURATION_CONFIG_ORCHESTRATOR_H

#include "components/configuration/manager/config_manager_template.h"
#include "components/configuration/repository/config_repo.h"

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes)

namespace nextgen::engine::configuration {

template <typename RenderingEngineType, typename VulkanRenderingApiType>
  requires EngineComponentTypeConcept<RenderingEngineType> &&
           EngineComponentTypeConcept<VulkanRenderingApiType>
struct ConfigOrchestrator {
  using RenderingEngineConfigType = typename RenderingEngineType::ConfigType;
  using VulkanRenderingApiConfigType =
      typename VulkanRenderingApiType::ConfigType;

  explicit ConfigOrchestrator(ConfigRepository& config_repo,
                              RenderingEngineType& rendering_engine,
                              VulkanRenderingApiType& vulkan_rendering_api)
      : rendering_config_manager_(rendering_engine,
                                  std::move(LoadRenderingConfig(config_repo))),
        vulkan_config_manager_(vulkan_rendering_api,
                               std::move(LoadVulkanConfig(config_repo))) {}

  void Configure() {
    vulkan_config_manager_.ConfigureComponent();
    rendering_config_manager_.ConfigureComponent();
  }

  ConfigComponentManager<RenderingEngineType> rendering_config_manager_;
  ConfigComponentManager<VulkanRenderingApiType> vulkan_config_manager_;

 private:
  // Helper functions to load configurations
  static auto LoadRenderingConfig(ConfigRepository& config_repo) {
    return config_repo["rendering"].LoadConfig<RenderingEngineConfigType>();
  }

  static auto LoadVulkanConfig(ConfigRepository& config_repo) {
    return config_repo["rendering"]["vulkan"]
        .LoadConfig<VulkanRenderingApiConfigType>();
  }
};

}  // namespace nextgen::engine::configuration
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes)

#endif
