#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_CONTEXT_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_CONTEXT_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan_core.h>

namespace nextgen::engine::rendering::vulkan {

struct VulkanContext {
  VkDevice device = 0;
  VkInstance instance = 0;
  GLFWwindow *window = 0;
  VkSurfaceKHR surface = 0;
  VkPhysicalDevice physical_device = 0;
  VkQueue graphics_queue = 0;
  VkSwapchainKHR swapchain = 0;
};

}  // namespace nextgen::engine::rendering::vulkan

#endif
