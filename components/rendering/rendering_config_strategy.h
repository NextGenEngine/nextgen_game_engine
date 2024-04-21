#ifndef NEXTGEN_ENGINE_RENDERING_CONFIG_STRATEGY_H
#define NEXTGEN_ENGINE_RENDERING_CONFIG_STRATEGY_H

#include "components/configuration/config_manager.h"
#include "components/engine/nextgen_game_engine_interfaces.h"
#include "components/engine/nextgen_game_engine_templates.h"
#include "components/rendering/directx/directx_config_strategy.h"
#include "components/rendering/rendering.h"
#include "components/rendering/rendering_config_strategy_default.h"
#include "components/rendering/rendering_config_strategy_primary.h"
#include "components/rendering/vulkan/vulkan_config_strategy.h"

namespace nextgen::engine::rendering {

using configuration::ComponentConfig;
using directx::DirectXDefaultConfigStrategy;
using interfaces::IConfigurationStrategy;
using templates::FallbackConfigurationStrategyTemplate;
using vulkan::VulkanDefaultConfigStrategy;

struct RenderingConfigurationStrategyData {
  RenderingConfigurationStrategySelector api_strategy_selector_;
};
struct RenderingConfigurationStrategy
    : RenderingConfigurationStrategyData,
      FallbackConfigurationStrategyTemplate<
          RenderingConfigurationPrimaryStrategy,
          RenderingConfigurationDefaultStrategy> {
  void Initialize(ComponentConfig component_config,
                  RenderingEngine& rendering_engine);
};

}  // namespace nextgen::engine::rendering

#endif
