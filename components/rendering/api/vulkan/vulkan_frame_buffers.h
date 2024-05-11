#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_FRAME_BUFFERS_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_FRAME_BUFFERS_H

#include <vulkan/vulkan_core.h>

#include <vector>

#include "components/rendering/api/vulkan/vulkan_context.h"

namespace nextgen::engine::rendering::vulkan {

struct FrameBuffers {
  VulkanContext* vulkan_context_;

  void Initialize(VulkanContext& vulkan_context);

  void createFramebuffers(VkDevice device, VkExtent2D swapChainExtent,
                          VkSwapchainKHR swapChain,
                          VkFormat swapChainImageFormat,
                          VkRenderPass renderPass);

  std::vector<VkImageView> createSwapChainImageViews(VkDevice device,
                                                     VkSwapchainKHR swapchain,
                                                     VkFormat imageFormat);
};

}  // namespace nextgen::engine::rendering::vulkan

#endif
