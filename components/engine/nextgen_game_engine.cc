#include "nextgen_game_engine.h"

#include <iostream>

#include "components/configuration/config_loader.h"
#include "components/configuration/config_manager.h"
#include "components/rendering/vulkan/vulkan_rendering.h"

auto configManager = ConfigManager(StringLoader(), "");
auto currentContext = createSystemContextWithLoader(
    configManager.getComponentConfig(), configManager);

auto configManagerFileLoader = ConfigManager(FileLoader(), "");

int main() {
  vulkan_create_device();
  vulkan_create_swapchain();
  vulkan_cleanup();

  std::cout << (configManager["rendering"]["vulkan"]["refreshRate"].IsDefined()
                    ? "true"
                    : "false")
            << '\n';

  std::cout << configManagerFileLoader["rendering"]["vulkan"]["refreshRate"]
                   .as<float>()
            << '\n';
}
