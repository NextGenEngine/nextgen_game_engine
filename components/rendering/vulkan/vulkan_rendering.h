#ifndef NEXTGEN_ENGINE_VULKAN_RENDERING_H
#define NEXTGEN_ENGINE_VULKAN_RENDERING_H

#include "components/configuration/config_manager.h"
#include "components/rendering/rendering_api.h"
#include "vulkan_config.h"

namespace nextgen::engine::rendering::vulkan {

using configuration::ComponentConfig;
using nextgen::engine::rendering::api::IRenderingApi;

class VulkanRenderingApi : public IRenderingApi {
  ComponentConfig componentConfig;
  VulkanConfig config;

 public:
  explicit VulkanRenderingApi(const ComponentConfig& componentConfig);
  void render() override;
};

}  // namespace nextgen::engine::rendering::vulkan

#endif
