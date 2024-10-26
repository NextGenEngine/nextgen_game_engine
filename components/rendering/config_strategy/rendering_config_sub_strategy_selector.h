#ifndef NEXTGEN_ENGINE_RENDERING_CONFIG_SUB_STRATEGY_SELECTOR_H
#define NEXTGEN_ENGINE_RENDERING_CONFIG_SUB_STRATEGY_SELECTOR_H

#include "components/rendering/api/directx/directx_config_strategy.h"
#include "components/rendering/api/vulkan/config_strategy/vulkan_config_strategy.h"
#include "components/rendering/rendering_config.h"
#include "components/rendering/rendering_engine.h"

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)
namespace nextgen::engine::rendering {

using configuration::ComponentConfig;
using directx::DirectXDefaultConfigStrategy;
using vulkan::VulkanConfigStrategy;

struct RenderingConfigurationStrategySelectorData {
  VulkanConfigStrategy vulkan_strategy_;
  DirectXDefaultConfigStrategy direct_x_strategy_;

  RenderingConfigurationStrategySelectorData(ComponentConfig& component_config,
                                             RenderingEngine& rendering_engine)
      : vulkan_strategy_(component_config.GetComponentConfig("vulkan"),
                         rendering_engine),
        direct_x_strategy_(component_config) {}
};
struct RenderingConfigurationStrategySelector
    : RenderingConfigurationStrategySelectorData {
  RenderingConfigurationStrategySelector(ComponentConfig& component_config,
                                         RenderingEngine& rendering_engine)
      : RenderingConfigurationStrategySelectorData(component_config,
                                                   rendering_engine) {}

  IConfigurationStrategy* SelectStrategy(RenderingAPIEnum api);

  void Initialize(ComponentConfig& component_config,
                  RenderingEngine& rendering_engine);
};

void InitializeSubStrategies(ComponentConfig& component_config,
                             RenderingConfigurationStrategySelector& selector,
                             RenderingEngine& rendering_engine);

}  // namespace nextgen::engine::rendering
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)

#endif
