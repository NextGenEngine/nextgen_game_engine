#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_CONFIG_STRATEGY_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_CONFIG_STRATEGY_H

#include "components/configuration/repository/config_repo.h"
#include "components/engine/nextgen_game_engine_interfaces.h"
#include "components/engine/nextgen_game_engine_templates.h"
#include "components/rendering/api/vulkan/config_strategy/vulkan_config_strategy_default.h"
#include "components/rendering/api/vulkan/config_strategy/vulkan_config_strategy_primary.h"
#include "components/rendering/api/vulkan/vulkan_rendering.h"
#include "components/rendering/rendering_engine.h"

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)
namespace nextgen::engine::rendering::vulkan {
using configuration::ConfigRepositoryNode;
using interfaces::IConfigurationStrategy;

struct VulkanConfigStrategy
    : templates::FallbackConfigurationStrategyTemplate<
          VulkanConfigurationPrimaryStrategy,
          VulkanConfigurationDefaultStrategy, vulkan::VulkanRenderingApi> {
  VulkanConfigStrategy(ComponentConfig component_config,
                       RenderingEngine& rendering_engine);
};

}  // namespace nextgen::engine::rendering::vulkan
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)

#endif
