#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_CONTEXT_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_CONTEXT_H

#include <vector>
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
  VkExtent2D swapChainExtent = {};
  VkRenderPass renderPass = 0;
  std::vector<VkImageView> swapChainImageViews;
  std::vector<VkFramebuffer> swapChainFramebuffers;
  std::vector<VkCommandBuffer> commandBuffers;
  VkPipelineLayout pipelineLayout;
  VkPipeline graphicsPipeline;
  VkBuffer vertexBuffer;
  VkDeviceMemory vertexBufferMemory;
  VkSemaphore imageAvailableSemaphore = 0;
  VkSemaphore renderFinishedSemaphore = 0;
  VkFence inFlightFence;
};

}  // namespace nextgen::engine::rendering::vulkan

#endif
