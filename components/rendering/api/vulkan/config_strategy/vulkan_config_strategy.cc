#include "vulkan_config_strategy.h"

#include "components/configuration/config_repo.h"
#include "components/engine/nextgen_game_engine_templates.h"
#include "components/rendering/rendering_engine.h"

namespace nextgen::engine::rendering::vulkan {
using configuration::ConfigRepositoryNode;

VulkanConfigStrategy::VulkanConfigStrategy(ComponentConfig component_config,
                                           RenderingEngine& rendering_engine)
    : FallbackConfigurationStrategyTemplate(
          component_config, rendering_engine.apis_.vulkan_rendering_api) {}

}  // namespace nextgen::engine::rendering::vulkan
