#ifndef NEXTGEN_ENGINE_RENDERING_CONFIG_SUB_STRATEGY_SELECTOR_H
#define NEXTGEN_ENGINE_RENDERING_CONFIG_SUB_STRATEGY_SELECTOR_H

#include "components/rendering/api/directx/directx_config_strategy.h"
#include "components/rendering/api/vulkan/config_strategy/vulkan_config_strategy.h"
#include "components/rendering/rendering_config.h"
#include "components/rendering/rendering_engine.h"

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)
namespace nextgen::engine::rendering {

using configuration::ConfigRepositoryNode;
using directx::DirectXDefaultConfigStrategy;
using vulkan::VulkanConfigStrategy;

struct RenderingConfigurationStrategySelector {
  RenderingConfigurationStrategySelector(ComponentConfig& component_config,
                                         RenderingEngine& rendering_engine);

  IConfigurationStrategy* SelectStrategy(RenderingAPIEnum api);
  void SelectAndConfigure(RenderingAPIEnum api);

  VulkanConfigStrategy vulkan_strategy_;
  DirectXDefaultConfigStrategy direct_x_strategy_;
};

}  // namespace nextgen::engine::rendering
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)

#endif
