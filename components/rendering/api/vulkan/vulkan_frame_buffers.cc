#include "components/rendering/api/vulkan/vulkan_frame_buffers.h"

#include <vulkan/vulkan_core.h>

#include <vector>

#include "components/rendering/api/vulkan/vulkan_context.h"

namespace nextgen::engine::rendering::vulkan {

void FrameBuffers::Initialize(VulkanContext& vulkan_context) {
  vulkan_context_ = &vulkan_context;
}

void FrameBuffers::createFramebuffers(VkDevice device,
                                      VkExtent2D swapChainExtent,
                                      VkSwapchainKHR swapChain,
                                      VkFormat swapChainImageFormat,
                                      VkRenderPass renderPass) {
  vulkan_context_->swapChainImageViews =
      createSwapChainImageViews(device, swapChain, swapChainImageFormat);

  auto& swapChainImageViews = vulkan_context_->swapChainImageViews;

  vulkan_context_->swapChainFramebuffers =
      std::vector<VkFramebuffer>(swapChainImageViews.size());

  for (size_t i = 0; i < swapChainImageViews.size(); i++) {
    VkImageView attachments[] = {swapChainImageViews[i]};

    VkFramebufferCreateInfo framebufferInfo{};
    framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferInfo.renderPass = renderPass;
    framebufferInfo.attachmentCount = 1;
    framebufferInfo.pAttachments = attachments;
    framebufferInfo.width = swapChainExtent.width;
    framebufferInfo.height = swapChainExtent.height;
    framebufferInfo.layers = 1;

    if (vkCreateFramebuffer(device, &framebufferInfo, nullptr,
                            &vulkan_context_->swapChainFramebuffers[i]) !=
        VK_SUCCESS) {
      throw std::runtime_error("failed to create framebuffer!");
    }
  }
}

std::vector<VkImageView> FrameBuffers::createSwapChainImageViews(
    VkDevice device, VkSwapchainKHR swapchain, VkFormat imageFormat) {
  uint32_t imageCount;
  vkGetSwapchainImagesKHR(device, swapchain, &imageCount, nullptr);
  std::vector<VkImage> swapChainImages(imageCount);
  vkGetSwapchainImagesKHR(device, swapchain, &imageCount,
                          swapChainImages.data());

  std::vector<VkImageView> swapChainImageViews(imageCount);
  for (size_t i = 0; i < swapChainImages.size(); i++) {
    VkImageViewCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    createInfo.image = swapChainImages[i];
    createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    createInfo.format = imageFormat;
    createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    createInfo.subresourceRange.baseMipLevel = 0;
    createInfo.subresourceRange.levelCount = 1;
    createInfo.subresourceRange.baseArrayLayer = 0;
    createInfo.subresourceRange.layerCount = 1;

    if (vkCreateImageView(device, &createInfo, nullptr,
                          &swapChainImageViews[i]) != VK_SUCCESS) {
      throw std::runtime_error(
          "failed to create image views for the swap chain!");
    }
  }

  return swapChainImageViews;
}

void cleanupSwapChainImageViews(VkDevice device,
                                std::vector<VkImageView>& swapChainImageViews) {
  for (auto imageView : swapChainImageViews) {
    vkDestroyImageView(device, imageView, nullptr);
  }
}

}  // namespace nextgen::engine::rendering::vulkan
