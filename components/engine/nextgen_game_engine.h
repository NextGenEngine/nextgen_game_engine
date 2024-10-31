#ifndef NEXTGEN_GAME_ENGINE__H
#define NEXTGEN_GAME_ENGINE__H

#include "components/configuration/orchestrator/config_orchestrator.h"
#include "components/configuration/repository/config_loader.h"
#include "components/configuration/repository/config_repo.h"
#include "components/rendering/api/vulkan/vulkan_rendering.h"
#include "components/rendering/rendering_engine.h"

namespace nextgen::engine {

using configuration::ConfigOrchestrator;
using configuration::ConfigRepository;
using configuration::ConfigRepositoryNode;
using configuration::IConfigLoader;
using rendering::RenderingEngine;
using rendering::vulkan::VulkanRenderingApi;

constexpr auto CONFIG_FILE_PATH = "config.yaml";
extern nextgen::engine::configuration::FileLoader file_loader;

// NOLINTBEGIN(misc-non-private-member-variables-in-classes)
struct NextGenEngine {
  explicit NextGenEngine();
  void Loop();
  static void Initialize();
  void Shutdown();

  ConfigRepository component_config_{file_loader};
  RenderingEngine rendering_engine_;
  ConfigOrchestrator<RenderingEngine, rendering::vulkan::VulkanRenderingApi>
      rendering_config_strategy_;
};
// NOLINTEND(misc-non-private-member-variables-in-classes)

// GLOBAL VARIABLE AS SINGLETON (instead of singleton as static method variable)
extern NextGenEngine ENGINE;

}  // namespace nextgen::engine

#endif
