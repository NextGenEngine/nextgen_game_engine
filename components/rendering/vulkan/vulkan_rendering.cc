#include "vulkan_rendering.h"

#include <vulkan/vulkan_core.h>

#include <cstdint>
#include <utility>

#include "components/configuration/config_manager.h"
#include "components/rendering/vulkan/vulkan_config.h"
#include "vulkan_operations.h"

using nextgen::engine::configuration::ComponentConfig;

namespace nextgen::engine::rendering::vulkan {

auto DefaultConfig = []() -> VulkanConfig {
  enumerateAvailableDevices();
  getRecommendedResolutionForDevice();

  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
  const uint32_t defaultDeviceIndex = prioritizedIndexes[0];
  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
  const VkPhysicalDeviceProperties& defaultDeviceProperties = devicesProperties
      [defaultDeviceIndex];  // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
  const auto* currentVideoMode = glfw_currentVideoMode;

  return VulkanConfig{
      .deviceID = defaultDeviceProperties.deviceID,
      .width = static_cast<uint32_t>(currentVideoMode->width),
      .height = static_cast<uint32_t>(currentVideoMode->height),
      .refreshRate = static_cast<float>(currentVideoMode->refreshRate)};
};

auto inline LoadConfig(auto& componentConfig) {
  vulkan_init();
  return componentConfig.template LoadConfigOrDefault<VulkanConfig>(
      DefaultConfig);
}

VulkanRenderingApi::VulkanRenderingApi(ComponentConfig _componentConfig)
    : componentConfig(std::move(_componentConfig)),
      config(LoadConfig(componentConfig)) {}

void VulkanRenderingApi::render() {}

}  // namespace nextgen::engine::rendering::vulkan
