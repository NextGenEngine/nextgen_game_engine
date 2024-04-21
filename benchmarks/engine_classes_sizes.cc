#include <iostream>

#include "components/configuration/config_manager.h"
#include "components/engine/nextgen_game_engine.h"
#include "components/rendering/api/vulkan/config_strategy/vulkan_config_strategy.h"
#include "components/rendering/api/vulkan/config_strategy/vulkan_config_strategy_default.h"
#include "components/rendering/api/vulkan/config_strategy/vulkan_config_strategy_primary.h"
#include "components/rendering/api/vulkan/vulkan_config.h"
#include "components/rendering/api/vulkan/vulkan_context.h"
#include "components/rendering/api/vulkan/vulkan_device.hh"
#include "components/rendering/api/vulkan/vulkan_instance.h"
#include "components/rendering/api/vulkan/vulkan_rendering.h"
#include "components/rendering/api/vulkan/vulkan_swapchain.h"
#include "components/rendering/config_strategy/rendering_config_strategy.h"
#include "components/rendering/config_strategy/rendering_config_strategy_default.h"
#include "components/rendering/config_strategy/rendering_config_strategy_primary.h"
#include "components/rendering/config_strategy/rendering_config_sub_strategy_selector.h"
#include "components/rendering/config_strategy/rendering_config_validator.h"
#include "components/rendering/rendering.h"
#include "components/rendering/rendering_config.h"

int main() {
  std::cout
      << "nextgen::engine::configuration::ConfigManager: "
      << sizeof(nextgen::engine::configuration::ConfigManager) << "\n"
      << "nextgen::engine::configuration::ComponentConfig: "
      << sizeof(nextgen::engine::configuration::ComponentConfig) << "\n"
      << "nextgen::engine::rendering::RenderingEngineConfig: "
      << sizeof(nextgen::engine::rendering::RenderingEngineConfig) << "\n"
      << "nextgen::engine::rendering::RenderingConfigurationStrategySelector: "
      << sizeof(
             nextgen::engine::rendering::RenderingConfigurationStrategySelector)
      << "\n"

      << "nextgen::engine::rendering::RenderingAPIEnum: "
      << sizeof(nextgen::engine::rendering::RenderingAPIEnum) << "\n"
      << "nextgen::engine::rendering::"
         "RenderingConfigurationPrimaryStrategyData: "
      << sizeof(nextgen::engine::rendering::
                    RenderingConfigurationPrimaryStrategyData)
      << "\n"
      << "nextgen::engine::rendering::RenderingConfigurationPrimaryStrategy: "
      << sizeof(
             nextgen::engine::rendering::RenderingConfigurationPrimaryStrategy)
      << "\n"
      << "nextgen::engine::rendering::"
         "RenderingConfigurationDefaultStrategyData: "
      << sizeof(nextgen::engine::rendering::
                    RenderingConfigurationDefaultStrategyData)
      << "\n"
      << "nextgen::engine::rendering::RenderingConfigurationDefaultStrategy: "
      << sizeof(
             nextgen::engine::rendering::RenderingConfigurationDefaultStrategy)
      << "\n"
      << "nextgen::engine::rendering::RenderingConfigurationStrategy: "
      << sizeof(nextgen::engine::rendering::RenderingConfigurationStrategy)
      << "\n"
      << "nextgen::engine::rendering::RenderingConfigValidator: "
      << sizeof(nextgen::engine::rendering::RenderingConfigValidator)
      << "\n"

      // VULKAN API
      << "nextgen::engine::rendering::vulkan::VulkanConfig: "
      << sizeof(nextgen::engine::rendering::vulkan::VulkanConfig) << "\n"
      << "nextgen::engine::rendering::vulkan::"
         "VulkanConfigurationPrimaryStrategyData: "
      << sizeof(nextgen::engine::rendering::vulkan::
                    VulkanConfigurationPrimaryStrategyData)
      << "\n"
      << "nextgen::engine::rendering::vulkan::"
         "VulkanConfigurationPrimaryStrategy: "
      << sizeof(nextgen::engine::rendering::vulkan::
                    VulkanConfigurationPrimaryStrategy)
      << "\n"
      << "nextgen::engine::rendering::vulkan::"
         "VulkanConfigurationDefaultStrategyData: "
      << sizeof(nextgen::engine::rendering::vulkan::
                    VulkanConfigurationDefaultStrategyData)
      << "\n"
      << "nextgen::engine::rendering::vulkan::"
         "VulkanConfigurationDefaultStrategy: "
      << sizeof(nextgen::engine::rendering::vulkan::
                    VulkanConfigurationDefaultStrategy)
      << "\n"
      << "nextgen::engine::rendering::vulkan::VulkanConfigStrategy: "
      << sizeof(nextgen::engine::rendering::vulkan::VulkanConfigStrategy)
      << "\n"

      << "nextgen::engine::rendering::vulkan::VulkanInstance: "
      << sizeof(nextgen::engine::rendering::vulkan::VulkanInstance) << "\n"
      << "nextgen::engine::rendering::vulkan::VulkanContext: "
      << sizeof(nextgen::engine::rendering::vulkan::VulkanContext) << "\n"
      << "nextgen::engine::rendering::vulkan::VulkanDevice: "
      << sizeof(nextgen::engine::rendering::vulkan::VulkanDevice) << "\n"
      << "nextgen::engine::rendering::vulkan::VulkanSwapChain: "
      << sizeof(nextgen::engine::rendering::vulkan::VulkanSwapChain) << "\n"
      << "nextgen::engine::rendering::vulkan::VulkanRenderingApi: "
      << sizeof(nextgen::engine::rendering::vulkan::VulkanRenderingApi) << "\n"

      << "nextgen::engine::rendering::RenderingEngineData: "
      << sizeof(nextgen::engine::rendering::RenderingEngineData) << "\n"
      << "nextgen::engine::rendering::RenderingEngine: "
      << sizeof(nextgen::engine::rendering::RenderingEngine) << "\n"

      << "nextgen::engine::NextGenEngine: "
      << sizeof(nextgen::engine::NextGenEngine) << "\n";
}
