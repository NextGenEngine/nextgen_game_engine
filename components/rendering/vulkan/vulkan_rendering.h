#ifndef NEXTGEN_ENGINE_VULKAN_RENDERING_H
#define NEXTGEN_ENGINE_VULKAN_RENDERING_H

#include "components/configuration/config_manager.h"
#include "vulkan_config.h"

class VulkanApi {
 private:
  ComponentConfig componentConfig;

 public:
  explicit VulkanApi(ComponentConfig componentConfig)
      : componentConfig(componentConfig.getSubConfig("vulkan")) {
    this->componentConfig.config["api"] = "Hello world!!!";
  }

  void render();

  // Delete copy constructor and copy assignment operator
  VulkanApi(const VulkanApi &) = delete;
  VulkanApi &operator=(const VulkanApi &) = delete;
  ~VulkanApi() = default;             // Default destructor
  VulkanApi(VulkanApi &&) = default;  // Default move constructor
  VulkanApi &operator=(VulkanApi &&) =
      default;  // Default move assignment operator
};

#endif
