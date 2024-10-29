#ifndef NEXTGEN_ENGINE_RENDERING_CONFIG_STRATEGY_H
#define NEXTGEN_ENGINE_RENDERING_CONFIG_STRATEGY_H

#include "components/configuration/repository/config_repo.h"
#include "components/engine/nextgen_game_engine_interfaces.h"
#include "components/engine/nextgen_game_engine_templates.h"
#include "components/rendering/rendering_engine.h"
#include "rendering_config_strategy_default.h"
#include "rendering_config_strategy_primary.h"

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes)
namespace nextgen::engine::rendering {

using configuration::ConfigRepositoryNode;
using templates::FallbackConfigurationStrategyTemplate;

struct RenderingConfigurationStrategy : interfaces::IConfigurationStrategy {
  explicit RenderingConfigurationStrategy(ComponentConfig component_config,
                                          RenderingEngine& rendering_engine);

  bool Configure() override;

  ComponentConfig component_config_;
  RenderingConfigurationStrategySelector api_strategy_selector_;
  RenderingConfigurationPrimaryStrategy primary_strategy_;
  RenderingConfigurationDefaultStrategy default_strategy_;
};

}  // namespace nextgen::engine::rendering
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes)

#endif
