#include "vulkan_rendering.h"

#include <vulkan/vulkan_core.h>

#include <cstdint>

#include "components/rendering/vulkan/vulkan_operations.h"
#include "vulkan_config.h"

VulkanConfig getDefaultConfig() {
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
}
