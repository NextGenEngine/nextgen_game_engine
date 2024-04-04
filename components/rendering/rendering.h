#ifndef NEXTGEN_ENGINE_RENDERING_H
#define NEXTGEN_ENGINE_RENDERING_H

#include "components/configuration/config_loader.h"
#include "components/configuration/config_manager.h"
#include "vulkan/vulkan_rendering.h"

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

template <typename RenderingApi, typename ConfigManagerType>
  requires RenderingApiConcept<RenderingApi, ConfigManagerType>
class SystemContext {
 private:
  RenderingEngine<RenderingApi, ConfigManagerType> renderingEngine;
  // Other engine modules...

 public:
  explicit SystemContext(ComponentConfig componentConfig,
                         ConfigManagerType configManager)
      : renderingEngine(RenderingEngine<RenderingApi, ConfigManagerType>(
            componentConfig, configManager)) {
    // Initialize modules with Api
  }

  void render() { renderingEngine.render(); }

  // Additional methods to interact with other engines
};

class SystemFactory {
 public:
  template <typename RenderingApi, typename ConfigManagerType>
    requires RenderingApiConcept<RenderingApi, ConfigManagerType>
  static SystemContext<RenderingApi, ConfigManagerType> createSystemContext(
      ComponentConfig componentConfig, ConfigManagerType configManager) {
    return SystemContext<RenderingApi, ConfigManagerType>(componentConfig,
                                                          configManager);
  }
};

template <typename ConfigLoaderType>
struct VulkanApiForLoader;

template <>
struct VulkanApiForLoader<ConfigManager<StringLoader>> {
  using type = VulkanApi<ConfigManager<StringLoader>>;
};

template <>
struct VulkanApiForLoader<ConfigManager<FileLoader>> {
  using type = VulkanApi<ConfigManager<FileLoader>>;
};

template <typename LoaderType>
auto createSystemContextWithLoader(ComponentConfig componentConfig,
                                   ConfigManager<LoaderType> configManager) {
  using VulkanApiType =
      typename VulkanApiForLoader<ConfigManager<LoaderType>>::type;
  return SystemFactory::createSystemContext<VulkanApiType,
                                            ConfigManager<LoaderType>>(
      componentConfig, configManager);
}

#endif
