#include "vulkan_rendering.h"

#include <iostream>

#include "components/rendering/vulkan/vulkan_config.h"

namespace nextgen::engine::rendering::vulkan {

void VulkanRenderingApi::Initialize() {
  vulkan_instance_.Initialize(vulkan_context_);
}
void VulkanRenderingApi::Shutdown() {}
void VulkanRenderingApi::ApplyConfiguration(const void* config) {
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-cstyle-cast,google-readability-casting)
  const auto* vulkan_config = (VulkanConfig*)config;
  std::cout << vulkan_config->device_id << "\n";
}

void VulkanRenderingApi::Render() {}

VulkanRenderingApi::~VulkanRenderingApi() = default;

}  // namespace nextgen::engine::rendering::vulkan
