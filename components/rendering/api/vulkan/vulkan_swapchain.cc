#include "components/rendering/api/vulkan/vulkan_swapchain.h"

#include <vulkan/vulkan_core.h>

#include <stdexcept>

#include "components/rendering/api/vulkan/vulkan_context.h"

namespace nextgen::engine::rendering::vulkan {

void VulkanSwapChain::Initialize(VulkanContext& vulkan_context) {
  vulkan_context_ = &vulkan_context;
}

void VulkanSwapChain::CreateSwapChain() const {
  auto& surface = vulkan_context_->surface;
  auto& device = vulkan_context_->device;
  auto& swapchain = vulkan_context_->swapchain;
  auto& swapChainExtent = vulkan_context_->swapChainExtent;

  swapChainExtent = {
      .width = 800,  // Simplification: Fixed size
      .height = 600,
  };

  // Create a swap chain for image presentation
  // This pseudo-code assumes surface has already been created
  const VkSwapchainCreateInfoKHR createInfo = {
      .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
      .surface = surface,
      .minImageCount = 2,                       // Double buffering
      .imageFormat = VK_FORMAT_B8G8R8A8_UNORM,  // Simplification
      .imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR,
      .imageExtent = swapChainExtent,
      .imageArrayLayers = 1,
      .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
      .presentMode = VK_PRESENT_MODE_FIFO_KHR,  // V-Sync enable
      .clipped = VK_TRUE,
      .oldSwapchain = VK_NULL_HANDLE,
  };

  if (vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapchain) !=
      VK_SUCCESS) {
    throw std::runtime_error("Failed to create swap chain");
  }
}

VulkanSwapChain::~VulkanSwapChain() {
  if (vulkan_context_ == nullptr || vulkan_context_->swapchain == nullptr ||
      vulkan_context_->device == nullptr) {
    return;
  }
  vkDestroySwapchainKHR(vulkan_context_->device, vulkan_context_->swapchain,
                        nullptr);
}

}  // namespace nextgen::engine::rendering::vulkan
