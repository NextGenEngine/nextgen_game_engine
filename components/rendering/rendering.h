#ifndef NEXTGEN_ENGINE_RENDERING_H
#define NEXTGEN_ENGINE_RENDERING_H

#include "components/configuration/config_manager.h"

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
  ComponentConfig config;
  RenderingApi renderingApi;

 public:
  explicit RenderingEngine(ComponentConfig config)
      : config(config.getSubConfig("rendering")), renderingApi(this->config) {}

  void render() {}
};

template <RenderingApiConcept RenderingApi>
class SystemContext {
 private:
  RenderingEngine<RenderingApi> renderingEngine;
  // Other engine modules...

 public:
  explicit SystemContext(ComponentConfig configManager)
      : renderingEngine(RenderingEngine<RenderingApi>(configManager)) {
    // Initialize modules with Api
  }

  void render() { renderingEngine.render(); }

  // Additional methods to interact with other engines
};

class SystemFactory {
 public:
  template <RenderingApiConcept RenderingApi>
  static SystemContext<RenderingApi> createSystemContext(
      ComponentConfig configManager) {
    return SystemContext<RenderingApi>(configManager);
  }
};

#endif
