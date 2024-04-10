#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_INSTANCE_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_INSTANCE_H

#include "components/rendering/vulkan/vulkan_config.h"
#include "components/rendering/vulkan/vulkan_context.h"

namespace nextgen::engine::rendering::vulkan {

class VulkanInstance {
  VulkanContext* m_vulkan_context;

 public:
  explicit VulkanInstance(VulkanContext* vulkan_context);
  VulkanConfig DefaultConfiguration();
  ~VulkanInstance();

  // copy
  VulkanInstance& operator=(const VulkanInstance&) = delete;
  VulkanInstance(const VulkanInstance&) = delete;
  // move
  VulkanInstance& operator=(VulkanInstance&&) = default;
  VulkanInstance(VulkanInstance&&) = default;
};

}  // namespace nextgen::engine::rendering::vulkan

#endif
