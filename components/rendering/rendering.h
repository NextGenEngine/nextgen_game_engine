#ifndef NEXTGEN_ENGINE_RENDERING_H
#define NEXTGEN_ENGINE_RENDERING_H

#include "components/configuration/config_manager.h"

template <typename T, typename ConfigManagerType>
concept RenderingApiConcept = requires(T api, ComponentConfig componentConfig,
                                       ConfigManagerType configManager) {
  { T(componentConfig, configManager) };
  { api.render() } -> std::same_as<void>;
};

template <typename RenderingApi, typename ConfigManagerType>
  requires RenderingApiConcept<RenderingApi, ConfigManagerType>
class RenderingEngine {
 private:
  ComponentConfig config;
  ConfigManagerType configManager;
  RenderingApi renderingApi;

 public:
  explicit RenderingEngine(ComponentConfig componentConfig,
                           ConfigManagerType configManager)
      : config(componentConfig.getSubConfig("rendering")),
        configManager(configManager),
        renderingApi(this->config, this->configManager) {}

  void render() {}
};

#endif
