#ifndef NEXTGEN_ENGINE_VULKAN_RENDERING_H
#define NEXTGEN_ENGINE_VULKAN_RENDERING_H

#include "components/configuration/config_manager.h"
#include "vulkan_config.h"

class VulkanApi {
 private:
  const ComponentConfig &componentConfig;

 public:
  explicit VulkanApi(const ComponentConfig &componentConfig)
      : componentConfig(componentConfig) {}

  void render();

  // Delete copy constructor and copy assignment operator
  VulkanApi(const VulkanApi &) = delete;
  VulkanApi &operator=(const VulkanApi &) = delete;
  ~VulkanApi() = default;            // Default destructor
  VulkanApi(VulkanApi &&) = delete;  // Default move constructor
  VulkanApi &operator=(VulkanApi &&) =
      delete;  // Default move assignment operator
};

#endif
