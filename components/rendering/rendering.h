#ifndef NEXTGEN_ENGINE_RENDERING_H
#define NEXTGEN_ENGINE_RENDERING_H

#include "components/configuration/config_manager.h"
#include "vulkan/vulkan_rendering.h"

template <typename T>
concept RenderingApiConcept = requires(T api, ComponentConfig& configManager) {
  { api.render() } -> std::same_as<void>;
  //   { api.loadConfig(configManager) } -> std::same_as<void>;
  //   { api.getState() } -> std::convertible_to<std::string>;
  //   { api.loadState(std::string{}) } -> std::same_as<void>;
  //   { api.loadDefaultConfig() } -> std::same_as<void>;
  //   { T(configManager) };  // Ensure constructible from ConfigManager
};

template <RenderingApiConcept RenderingApi>
class RenderingEngine {
 private:
  RenderingApi renderingApi;

 public:
  explicit RenderingEngine(const ComponentConfig& configManager)
      : renderingApi(RenderingApi(configManager)) {
    // Initialize modules with Api
  }
  void render() {
    // API-specific rendering logic
  }
};

template <RenderingApiConcept RenderingApi>
class SystemContext {
 private:
  RenderingEngine<RenderingApi> renderingEngine;
  // Other engine modules...

 public:
  explicit SystemContext(const ComponentConfig& configManager)
      : renderingEngine(RenderingEngine<RenderingApi>(
            configManager.getSubConfig("rendering"))) {
    // Initialize modules with Api
  }

  void render() { renderingEngine.render(); }

  // Additional methods to interact with other engines
};

class SystemFactory {
 public:
  template <RenderingApiConcept RenderingApi>
  static SystemContext<RenderingApi> createSystemContext(
      const ComponentConfig& configManager) {
    return SystemContext<RenderingApi>(configManager);
  }
};

auto configManager = ConfigManager_File("");

// Pass vulkanComponentConfig directly without taking its address.
auto currentContext = SystemFactory::createSystemContext<VulkanApi>(
    configManager.getComponentConfig());

#endif
