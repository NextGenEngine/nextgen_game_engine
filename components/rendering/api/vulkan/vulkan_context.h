#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_CONTEXT_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_CONTEXT_H

#include <vector>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan_core.h>

#include "components/rendering/api/vulkan/vulkan_types.h"

namespace nextgen::engine::rendering::vulkan {

struct VulkanContext {
  bool enable_validation_layers = false;
  std::vector<const char *> validation_layers = {"VK_LAYER_KHRONOS_validation"};
  VkDebugUtilsMessengerEXT debug_messenger;

  VkInstance instance{};
  GLFWwindow *window{};
  VkSurfaceKHR surface{};

  VkDevice device{};
  VkPhysicalDevice physical_device{};
  VkQueue graphics_queue{};
  VkQueue present_queue{};

  VkSwapchainKHR swapchain{};
  std::vector<VkImage> swap_chain_images;
  VkFormat swap_chain_image_format{};
  VkExtent2D swap_chain_extent{};
  std::vector<VkImageView> swap_chain_image_views;
  std::vector<VkFramebuffer> swap_chain_framebuffers;

  VkImage depth_image{};
  VkDeviceMemory depth_image_memory{};
  VkImageView depth_image_view{};

  VkImage texture_image{};
  VkDeviceMemory texture_image_memory{};
  VkImageView texture_image_view{};
  VkSampler texture_sampler{};

  std::vector<Vertex> vertices;
  std::vector<uint32_t> indices;
  VkBuffer vertex_buffer{};
  VkDeviceMemory vertex_buffer_memory{};
  VkBuffer index_buffer{};
  VkDeviceMemory index_buffer_memory{};

  std::vector<VkBuffer> uniform_buffers;
  std::vector<VkDeviceMemory> uniform_buffers_memory;
  std::vector<void *> uniform_buffers_mapped;

  VkDescriptorPool descriptor_pool{};
  std::vector<VkDescriptorSet> descriptor_sets;

  VkRenderPass render_pass{};
  VkDescriptorSetLayout descriptor_set_layout{};
  VkPipelineLayout pipeline_layout{};
  VkPipeline graphics_pipeline{};

  VkCommandPool command_pool{};

  std::vector<VkCommandBuffer> command_buffers;

  std::vector<VkSemaphore> image_available_semaphores;
  std::vector<VkSemaphore> render_finished_semaphores;
  std::vector<VkFence> in_flight_fences;

  uint32_t current_frame = 0;
  bool framebuffer_resized = false;
};

}  // namespace nextgen::engine::rendering::vulkan

#endif
