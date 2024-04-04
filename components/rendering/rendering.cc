#include "rendering.h"

#include <iostream>

#include "components/configuration/config_loader.h"
#include "components/configuration/config_manager.h"
#include "components/rendering/vulkan/vulkan_operations.h"

auto configManager = ConfigManager(StringLoader(), "");
auto currentContext = createSystemContextWithLoader(
    configManager.getComponentConfig(), configManager);

int main() {
  vulkan_create_device();
  vulkan_create_swapchain();
  vulkan_cleanup();

  std::cout << (configManager["rendering"]["vulkan"]["refreshRate"].IsDefined()
                    ? "true"
                    : "false")
            << '\n';

  std::cout << configManager["rendering"]["vulkan"]["refreshRate"].as<float>()
            << '\n';
}
