#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_DEVICE_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_DEVICE_H

#include "vulkan_context.h"

namespace nextgen::engine::rendering::vulkan {

using nextgen::engine::rendering::vulkan::VulkanContext;

class VulkanDevice {
  VulkanContext* m_vulkan_context;

 public:
  explicit VulkanDevice(VulkanContext* vulkan_context);
  ~VulkanDevice();

  // copy
  VulkanDevice& operator=(const VulkanDevice&) = delete;
  VulkanDevice(const VulkanDevice&) = delete;
  // move
  VulkanDevice& operator=(VulkanDevice&&) = default;
  VulkanDevice(VulkanDevice&&) = default;
};

}  // namespace nextgen::engine::rendering::vulkan

#endif
