#include "vulkan_init.h"

#include <vulkan/vulkan_core.h>
#include <yaml-cpp/exceptions.h>

#include <cstdint>
#include <iostream>

#include "components/configuration/config_manager.h"
#include "components/configuration/config_manager_globals.h"
#include "vulkan_config.h"
#include "vulkan_operations.h"

VulkanConfig vulkan_config{};
ComponentConfig vulkan_component_config;

void LoadVulkanConfig() {
  vulkan_init();
  try {
    // Attempt to use the provided configuration
    vulkan_config = vulkan_component_config().as<VulkanConfig>();
  } catch (const YAML::Exception& e) {
    // Log the error and use default values on failure
    std::cerr << "Failed to decode VulkanConfig: " << e.what() << "\n";
    vulkan_config = GetDefaultConfig();
    vulkan_component_config() = vulkan_config;
    CONFIG_MANAGER.Save();
  }
  std::cout << "config loaded\n";
}

VulkanConfig GetDefaultConfig() {
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

void SetComponentConfig(const ComponentConfig& componentConfig) {
  vulkan_component_config = componentConfig;
}
