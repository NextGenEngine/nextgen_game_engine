#include <iostream>

#include "components/rendering/vulkan/vulkan_rendering.h"

extern "C" {
#include "components/rendering/vulkan/vulkan_operations.h"
}

#include "components/configuration/config_manager.h"
#include "rendering.h"

auto configManager = ConfigManager_String("");
// Pass vulkanComponentConfig directly without taking its address.
auto currentContext = SystemFactory::createSystemContext<VulkanApi>(
    configManager.getComponentConfig());

int main() {
  vulkan_init();
  vulkan_create_device();
  vulkan_create_swapchain();
  enumerateAvailableDevices();
  vulkan_cleanup();

  std::cout << (configManager.config["rendering"]["vulkan"]["api"].IsDefined()
                    ? "true"
                    : "false")
            << '\n';

  std::cout
      << configManager.config["rendering"]["vulkan"]["api"].as<std::string>()
      << '\n';
}
