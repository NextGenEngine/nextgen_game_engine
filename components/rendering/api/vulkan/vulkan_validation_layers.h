#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_VALIDATION_LAYERS_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_VALIDATION_LAYERS_H

#include <vector>

#include "vulkan_context.h"

namespace nextgen::engine::rendering::vulkan {

struct VulkanValidationLayers {
  void Initialize(VulkanContext& vulkan_context);

  void StartUp();
  void Shutdown() const;

  static void PopulateDebugMessengerCreateInfo(
      VkDebugUtilsMessengerCreateInfoEXT& createInfo);
  static bool CheckValidationLayerSupport();
  static bool Enabled();
  static const std::vector<const char*>& GetValidationLayers();

  VulkanContext* vulkan_context_;
  VkDebugUtilsMessengerEXT debugMessenger;
};

}  // namespace nextgen::engine::rendering::vulkan

#endif
