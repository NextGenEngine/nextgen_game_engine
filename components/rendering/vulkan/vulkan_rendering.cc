#include "vulkan_rendering.h"

#include <utility>

#include "components/configuration/config_manager.h"
#include "components/rendering/vulkan/vulkan_config.h"
#include "components/rendering/vulkan/vulkan_context.h"
#include "components/rendering/vulkan/vulkan_device.hh"
#include "components/rendering/vulkan/vulkan_instance.h"
#include "vulkan_config.h"

using nextgen::engine::configuration::ComponentConfig;

namespace nextgen::engine::rendering::vulkan {

VulkanRenderingApi::VulkanRenderingApi(ComponentConfig component_config)
    : m_componentConfig(std::move(component_config)),
      m_vulkan_context(VulkanContext{}),
      m_vulkan_instance(VulkanInstance(&this->m_vulkan_context)),
      m_config(LoadConfigOrDefault()),
      m_vulkan_device(VulkanDevice(&this->m_vulkan_context)),
      m_vulkan_swap_chain(&this->m_vulkan_context) {}

VulkanConfig VulkanRenderingApi::LoadConfigOrDefault() {
  auto config = m_componentConfig.LoadConfig<VulkanConfig>();
  if (config) {
    return config.value();
  }
  // If configuration was not loaded, than fall back to default one
  auto defaultConfig = m_vulkan_instance.DefaultConfiguration();
  m_componentConfig.UpdateConfig(defaultConfig);
  m_componentConfig.SaveConfig();
  return defaultConfig;
}

void VulkanRenderingApi::render() {}

VulkanRenderingApi::~VulkanRenderingApi() = default;

}  // namespace nextgen::engine::rendering::vulkan
