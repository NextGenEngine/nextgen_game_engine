#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_CONFIG_STRATEGY_PRIMARY_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_CONFIG_STRATEGY_PRIMARY_H

#include "components/rendering/api/vulkan/vulkan_rendering.h"

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)
namespace nextgen::engine::rendering::vulkan {
using interfaces::IConfigurationStrategy;

struct VulkanConfigurationPrimaryStrategyData {
  ComponentConfig& component_config_;
  vulkan::VulkanRenderingApi& vulkan_rendering_api_;
};
struct VulkanConfigurationPrimaryStrategy
    : VulkanConfigurationPrimaryStrategyData,
      IConfigurationStrategy {
  bool Configure() override;

  VulkanConfigurationPrimaryStrategy(ComponentConfig& component_config,
                                     VulkanRenderingApi& vulkan_rendering_api);
};

}  // namespace nextgen::engine::rendering::vulkan
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)

#endif
