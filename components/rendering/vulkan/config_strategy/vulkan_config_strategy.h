#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_CONFIG_STRATEGY_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_CONFIG_STRATEGY_H

#include "components/configuration/config_manager.h"
#include "components/engine/nextgen_game_engine_interfaces.h"
#include "components/engine/nextgen_game_engine_templates.h"
#include "components/rendering/vulkan/config_strategy/vulkan_config_strategy_default.h"
#include "components/rendering/vulkan/config_strategy/vulkan_config_strategy_primary.h"
#include "components/rendering/vulkan/vulkan_rendering.h"

namespace nextgen::engine::rendering::vulkan {
using configuration::ComponentConfig;
using interfaces::IConfigurationStrategy;

struct VulkanConfigStrategy : templates::FallbackConfigurationStrategyTemplate<
                                  VulkanConfigurationPrimaryStrategy,
                                  VulkanConfigurationDefaultStrategy> {
  void Initialize(ComponentConfig component_config,
                  VulkanRenderingApi& vulkan_rendering_api);
};

}  // namespace nextgen::engine::rendering::vulkan

#endif
