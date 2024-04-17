#ifndef NEXTGEN_ENGINE_RENDERING_CONFIG_STRATEGY_H
#define NEXTGEN_ENGINE_RENDERING_CONFIG_STRATEGY_H

#include <stdexcept>

#include "components/configuration/config_manager.h"
#include "components/engine/nextgen_game_engine_interfaces.h"
#include "components/engine/nextgen_game_engine_templates.h"
#include "components/rendering/directx/directx_config_strategy.h"
#include "components/rendering/rendering.h"
#include "components/rendering/rendering_config.h"
#include "components/rendering/vulkan/vulkan_config_strategy.h"

namespace nextgen::engine::rendering {

using configuration::ComponentConfig;
using directx::DirectXDefaultConfigStrategy;
using interfaces::IConfigurationStrategy;
using templates::FallbackConfigurationStrategyTemplate;
using vulkan::VulkanDefaultConfigStrategy;

// NOLINTBEGIN(misc-non-private-member-variables-in-classes)
struct RenderingConfigurationStrategySelector {
  IConfigurationStrategy* SelectStrategy(RenderingAPIEnum api) {
    switch (api) {
      case RenderingAPIEnum::Vulkan:
        return &vulkan_strategy_;
      case RenderingAPIEnum::DirectX:
        return &direct_x_strategy_;
      case RenderingAPIEnum::OpenGL:
        throw std::runtime_error("Haha. OpenGL is unsupported");
      default:
        throw std::runtime_error("Uhh... unknown rendering api");
    }
  }

  VulkanDefaultConfigStrategy vulkan_strategy_;
  DirectXDefaultConfigStrategy direct_x_strategy_;
};

struct RenderingConfigurationPrimaryStrategy : IConfigurationStrategy {
  void Configure() override {
    auto rendering_engine_config =
        component_config_.LoadConfig<RenderingEngineConfig>();

    auto* strategy =
        api_strategy_selector_.SelectStrategy(rendering_engine_config->api);
    strategy->Configure();
  }

  void Initialize(ComponentConfig component_config,
                  RenderingEngine& rendering_engine) {
    component_config_ = component_config;
    rendering_engine_ = &rendering_engine;
    api_strategy_selector_.vulkan_strategy_.Initialize(
        component_config, rendering_engine.apis_.vulkan_rendering_api);
  }

  ComponentConfig component_config_;
  RenderingConfigurationStrategySelector api_strategy_selector_;
  RenderingEngine* rendering_engine_;
};

auto DefaultConfig = []() -> RenderingEngineConfig {
  return RenderingEngineConfig{.api = RenderingAPIEnum::Vulkan};
};

struct RenderingConfigurationDefaultStrategy : IConfigurationStrategy {
  void Configure() override {
    auto rendering_engine_config = DefaultConfig();
    component_config_.UpdateConfig(rendering_engine_config);
    component_config_.SaveConfig();
    rendering_engine_->ApplyConfiguration(&rendering_engine_config);

    auto* sub_component_strategy =
        api_strategy_selector_.SelectStrategy(rendering_engine_config.api);
    sub_component_strategy->Configure();
  }

  void Initialize(ComponentConfig component_config,
                  RenderingEngine& rendering_engine) {
    rendering_engine_ = &rendering_engine;
    component_config_ = component_config;
    api_strategy_selector_.vulkan_strategy_.Initialize(
        component_config, rendering_engine.apis_.vulkan_rendering_api);
  }

  ComponentConfig component_config_;
  RenderingConfigurationStrategySelector api_strategy_selector_;
  RenderingEngine* rendering_engine_;
};

struct RenderingConfigValidator {
  bool Validate(RenderingEngineConfig config) {
    switch (config.api) {
      case RenderingAPIEnum::Vulkan:
      case RenderingAPIEnum::OpenGL:
      case RenderingAPIEnum::DirectX:
        break;
      default:
        return false;
    }
    return true;
  }
};

struct RenderingConfigurationFallbackStrategy
    : FallbackConfigurationStrategyTemplate<
          rendering::RenderingEngineConfig, rendering::RenderingConfigValidator,
          RenderingConfigurationPrimaryStrategy,
          RenderingConfigurationDefaultStrategy, RenderingEngine> {
  void Initialize(ComponentConfig component_config,
                  RenderingEngine& rendering_engine) {
    primary_strategy_.Initialize(component_config, rendering_engine);
    default_strategy_.Initialize(component_config, rendering_engine);
  }
};

// NOLINTEND(misc-non-private-member-variables-in-classes)

}  // namespace nextgen::engine::rendering

#endif
