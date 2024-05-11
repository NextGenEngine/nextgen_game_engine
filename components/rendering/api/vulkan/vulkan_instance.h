#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_INSTANCE_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_INSTANCE_H

#include "components/rendering/api/vulkan/vulkan_config.h"
#include "components/rendering/api/vulkan/vulkan_context.h"

namespace nextgen::engine::rendering::vulkan {

// NOLINTBEGIN(misc-non-private-member-variables-in-classes)
struct VulkanInstance {
  VulkanContext* vulkan_context_{};

 public:
  explicit VulkanInstance();

  void Initialize(VulkanContext& vulkan_context);

  void StartUp();
  void Shutdown() const;

  ~VulkanInstance() = default;

  VulkanConfig GetDefaultConfiguration() const;

  // copy
  VulkanInstance& operator=(const VulkanInstance&) = delete;
  VulkanInstance(const VulkanInstance&) = delete;
  // move
  VulkanInstance& operator=(VulkanInstance&&) = default;
  VulkanInstance(VulkanInstance&&) = default;
};
// NOLINTEND(misc-non-private-member-variables-in-classes)

}  // namespace nextgen::engine::rendering::vulkan

#endif
