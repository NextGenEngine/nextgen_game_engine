#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_CONFIG_STRATEGY_DEFAULT_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_CONFIG_STRATEGY_DEFAULT_H

#include "components/rendering/api/vulkan/vulkan_rendering.h"

namespace nextgen::engine::rendering::vulkan {
using interfaces::IConfigurationStrategy;

struct VulkanConfigurationDefaultStrategyData {
  ComponentConfig component_config_;
  vulkan::VulkanRenderingApi* vulkan_rendering_api_;
};
struct VulkanConfigurationDefaultStrategy
    : VulkanConfigurationDefaultStrategyData,
      IConfigurationStrategy {
  bool Configure() override;

  void Initialize(ComponentConfig component_config,
                  VulkanRenderingApi& vulkan_rendering_api);
};

}  // namespace nextgen::engine::rendering::vulkan

#endif
