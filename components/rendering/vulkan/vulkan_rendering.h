#ifndef NEXTGEN_ENGINE_VULKAN_RENDERING_H
#define NEXTGEN_ENGINE_VULKAN_RENDERING_H

#include "components/configuration/config_manager.h"
#include "components/rendering/rendering_api.h"
#include "components/rendering/vulkan/vulkan_context.h"
#include "components/rendering/vulkan/vulkan_device.hh"
#include "components/rendering/vulkan/vulkan_instance.h"
#include "components/rendering/vulkan/vulkan_swapchain.h"
#include "vulkan_config.h"

namespace nextgen::engine::rendering::vulkan {

using configuration::ComponentConfig;
using nextgen::engine::rendering::api::IRenderingApi;

class VulkanRenderingApi : public IRenderingApi {
  ComponentConfig m_componentConfig;

  /* SUB COMPONENTS - order here is crucial. For example, m_config can be
   * initialized only when Vulkan instance is already in place for default
   * configuration to load if needed (detecting recommended graphics device and
   * resolution)*/
  VulkanContext m_vulkan_context;
  VulkanInstance m_vulkan_instance;
  VulkanConfig m_config;
  VulkanDevice m_vulkan_device;
  VulkanSwapChain m_vulkan_swap_chain;

 public:
  explicit VulkanRenderingApi(ComponentConfig component_config);
  void render() override;

  ~VulkanRenderingApi() override;

  // copy
  VulkanRenderingApi(const VulkanRenderingApi&) = delete;
  VulkanRenderingApi& operator=(const VulkanRenderingApi&) = delete;
  // move
  VulkanRenderingApi(VulkanRenderingApi&&) noexcept = default;
  VulkanRenderingApi& operator=(VulkanRenderingApi&&) noexcept = default;

 private:
  VulkanConfig LoadConfigOrDefault();
};

}  // namespace nextgen::engine::rendering::vulkan

#endif
