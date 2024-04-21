#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_CONFIG_STRATEGY_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_CONFIG_STRATEGY_H

#include "components/configuration/config_manager.h"
#include "components/engine/nextgen_game_engine_interfaces.h"
#include "components/rendering/vulkan/vulkan_rendering.h"

namespace nextgen::engine::rendering::vulkan {
using configuration::ComponentConfig;
using interfaces::IConfigurationStrategy;

// NOLINTBEGIN(misc-non-private-member-variables-in-classes)
struct VulkanDefaultConfigStrategy : IConfigurationStrategy {
  ComponentConfig component_config_;
  VulkanRenderingApi* vulkan_rendering_api_;

  bool Configure() override;
  void Initialize(ComponentConfig component_config,
                  VulkanRenderingApi& vulkan_rendering_api) {
    component_config_ = component_config;
    vulkan_rendering_api_ = &vulkan_rendering_api;
  }
};
// NOLINTEND(misc-non-private-member-variables-in-classes)

}  // namespace nextgen::engine::rendering::vulkan

#endif
