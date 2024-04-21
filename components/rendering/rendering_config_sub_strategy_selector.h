#ifndef NEXTGEN_ENGINE_RENDERING_CONFIG_SUB_STRATEGY_SELECTOR_H
#define NEXTGEN_ENGINE_RENDERING_CONFIG_SUB_STRATEGY_SELECTOR_H

#include "components/engine/nextgen_game_engine_interfaces.h"
#include "components/rendering/directx/directx_config_strategy.h"
#include "components/rendering/rendering.h"
#include "components/rendering/rendering_config.h"
#include "components/rendering/vulkan/vulkan_config_strategy.h"

namespace nextgen::engine::rendering {

using configuration::ComponentConfig;
using directx::DirectXDefaultConfigStrategy;
using nextgen::engine::interfaces::IConfigurationStrategy;
using vulkan::VulkanDefaultConfigStrategy;

struct RenderingConfigurationStrategySelectorData {
  VulkanDefaultConfigStrategy vulkan_strategy_;
  DirectXDefaultConfigStrategy direct_x_strategy_;
};
struct RenderingConfigurationStrategySelector
    : RenderingConfigurationStrategySelectorData {
  IConfigurationStrategy* SelectStrategy(RenderingAPIEnum api);
};

void InitializeSubStrategies(ComponentConfig& component_config,
                             RenderingConfigurationStrategySelector& selector,
                             RenderingEngine& rendering_engine);

}  // namespace nextgen::engine::rendering

#endif
