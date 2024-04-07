#include <cstdlib>
#include <iostream>

#include "components/configuration/config_manager.h"
#include "components/configuration/config_manager_globals.h"
#include "components/rendering/rendering.h"
#include "components/rendering/vulkan/vulkan_rendering.h"

using VulkanRenderer = rendering::RenderingEngine<rendering::VulkanRenderer>;

int main() {
  VulkanRenderer::init(CONFIG_MANAGER.getComponentConfig()
                           .getSubConfig("rendering")
                           .getSubConfig("vulkan"));

  std::cout << (CONFIG_MANAGER["rendering"]["vulkan"]["refreshRate"].IsDefined()
                    ? "true"
                    : "false")
            << '\n';

  std::cout << "Vulkan config: " << CONFIG_MANAGER["rendering"]["vulkan"]
            << '\n';

  std::cout << "Successful exit.\n";
  return EXIT_SUCCESS;
}
