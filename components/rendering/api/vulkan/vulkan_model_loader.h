#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_MODEL_LOADER_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_MODEL_LOADER_H

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes)
#include "components/rendering/api/vulkan/vulkan_context.h"
namespace nextgen::engine::rendering::vulkan {

struct VulkanModelLoader {
  VulkanContext* vulkan_context_{};

  VulkanModelLoader();

  void Initialize(VulkanContext& vulkan_context);
  void Shutdown() const noexcept;

  ~VulkanModelLoader();

  // copy
  VulkanModelLoader& operator=(const VulkanModelLoader&) = delete;
  VulkanModelLoader(const VulkanModelLoader&) = delete;
  // move
  VulkanModelLoader& operator=(VulkanModelLoader&&) = default;
  VulkanModelLoader(VulkanModelLoader&&) = default;

 private:
  void LoadModel() const;
};

}  // namespace nextgen::engine::rendering::vulkan
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes)

#endif
