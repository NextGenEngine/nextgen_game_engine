#include "vulkan_rendering.h"

#include <iostream>

#include "components/configuration/config_manager.h"
#include "vulkan_init.h"

namespace rendering {

void VulkanRenderer::init(const ComponentConfig& componentConfig) {
  SetComponentConfig(componentConfig);
  LoadVulkanConfig();
  std::cout << "Vulkan initialized\n";
}

void VulkanRenderer::render() { std::cout << "Rendering with Vulkan\n"; }

}  // namespace rendering
