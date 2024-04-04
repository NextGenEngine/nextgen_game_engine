#ifndef NEXTGEN_GAME_ENGINE_H
#define NEXTGEN_GAME_ENGINE_H

#include "components/configuration/config_loader.h"
#include "components/configuration/config_manager.h"
#include "components/rendering/rendering.h"
#include "components/rendering/vulkan/vulkan_rendering.h"

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
