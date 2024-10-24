#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_VALIDATION_LAYERS_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_VALIDATION_LAYERS_H

#include <vector>

#include "vulkan_context.h"

namespace nextgen::engine::rendering::vulkan {

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)
struct VulkanValidationLayers {
  VulkanContext& vulkan_context_;
  VkDebugUtilsMessengerEXT debugMessenger;

  explicit VulkanValidationLayers(VulkanContext& vulkan_context);
  void Initialize();

  void Shutdown() const;

  static void PopulateDebugMessengerCreateInfo(
      VkDebugUtilsMessengerCreateInfoEXT& createInfo);
  static bool CheckValidationLayerSupport();
  static bool Enabled();
  static const std::vector<const char*>& GetValidationLayers();
};

}  // namespace nextgen::engine::rendering::vulkan
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)

#endif
