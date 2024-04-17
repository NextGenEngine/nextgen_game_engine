#ifndef NEXTGEN_GAME_ENGINE__H
#define NEXTGEN_GAME_ENGINE__H

#include <iostream>

#include "components/configuration/config_loader.h"
#include "components/configuration/config_manager.h"
#include "components/engine/nextgen_game_engine_templates.h"
#include "components/rendering/rendering.h"
#include "components/rendering/rendering_config_strategy.h"

namespace nextgen::engine {

using configuration::ComponentConfig;
using configuration::IConfigLoader;
using rendering::RenderingConfigurationFallbackStrategy;
using rendering::RenderingConfigurationPrimaryStrategy;
using rendering::RenderingEngine;
using templates::FallbackConfigurationStrategyTemplate;

constexpr std::string_view CONFIG_FILE_PATH = "config.yaml";

// NOLINTBEGIN(misc-non-private-member-variables-in-classes)
struct NextGenEngine {
  explicit NextGenEngine() { std::cout << "NextGenEngine object created\n"; }
  void Loop();

  void Initialize(ComponentConfig component_config) {
    std::cout << "NextGenEngine object is singleton. Its implemented as global "
                 "variable visible to all translation units. All engine "
                 "components and sub-components are direct part of engine "
                 "singleton. So all their fields are available already before "
                 "main. Here we just need to initialize its properties, before "
                 "it can be configured and started\n";
    component_config_ = component_config;
    rendering_engine_.Initialize();
    rendering_config_strategy_.Initialize(component_config, rendering_engine_);

    std::cout << "NextGenGame engine factory done.\n";
    rendering_engine_.apis_.vulkan_rendering_api.config_.device_id = 5;
    rendering_engine_.apis_.vulkan_rendering_api.config_.height = 3;
    std::cout << "Device id="
              << rendering_engine_.apis_.vulkan_rendering_api.m_vulkan_device
                     .m_vulkan_config->device_id
              << "\n";
  }

  ComponentConfig component_config_;
  RenderingEngine rendering_engine_;

  RenderingConfigurationFallbackStrategy rendering_config_strategy_;
  // RenderingConfigurationStrategy rendering_config_strategy_;
};
// NOLINTEND(misc-non-private-member-variables-in-classes)

// GLOBAL VARIABLE AS SINGLETON (instead of singleton as static method variable)
extern NextGenEngine ENGINE;

}  // namespace nextgen::engine

#endif
