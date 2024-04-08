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
  explicit VulkanRenderingApi(ComponentConfig componentConfig);
  void render() override;

  ~VulkanRenderingApi() override;

  // Explicitly delete the copy constructor and copy assignment operator
  VulkanRenderingApi(const VulkanRenderingApi&) = delete;
  VulkanRenderingApi& operator=(const VulkanRenderingApi&) = delete;

  // Default move constructor and move assignment operator
  VulkanRenderingApi(VulkanRenderingApi&&) noexcept = default;
  VulkanRenderingApi& operator=(VulkanRenderingApi&&) noexcept = default;
};

}  // namespace nextgen::engine::rendering::vulkan

#endif
