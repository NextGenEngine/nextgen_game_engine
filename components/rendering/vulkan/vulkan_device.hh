#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_DEVICE_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_DEVICE_H

#include <iostream>

#include "components/rendering/vulkan/vulkan_config.h"
#include "vulkan_context.h"

namespace nextgen::engine::rendering::vulkan {

using nextgen::engine::rendering::vulkan::VulkanContext;

// NOLINTBEGIN(misc-non-private-member-variables-in-classes)
struct VulkanDevice {
  VulkanConfig* m_vulkan_config{};
  VulkanContext* m_vulkan_context{};

 public:
  explicit VulkanDevice() { std::cout << "VulkanDevice object created\n"; }

  explicit VulkanDevice(VulkanContext* vulkan_context);
  ~VulkanDevice();

  // copy
  VulkanDevice& operator=(const VulkanDevice&) = delete;
  VulkanDevice(const VulkanDevice&) = delete;
  // move
  VulkanDevice& operator=(VulkanDevice&&) = default;
  VulkanDevice(VulkanDevice&&) = default;
};
// NOLINTEND(misc-non-private-member-variables-in-classes)

}  // namespace nextgen::engine::rendering::vulkan

#endif
