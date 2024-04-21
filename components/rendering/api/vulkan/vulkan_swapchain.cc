#include "components/rendering/api/vulkan/vulkan_swapchain.h"

#include <vulkan/vulkan_core.h>

#include <stdexcept>

#include "components/rendering/api/vulkan/vulkan_context.h"

namespace nextgen::engine::rendering::vulkan {

VulkanSwapChain::VulkanSwapChain(VulkanContext* vulkan_context)
    : m_vulkanContext(vulkan_context) {
  auto& surface = m_vulkanContext->surface;
  auto& device = m_vulkanContext->device;
  auto& swapchain = m_vulkanContext->swapchain;

  // Create a swap chain for image presentation
  // This pseudo-code assumes surface has already been created
  const VkSwapchainCreateInfoKHR createInfo = {
      .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
      .surface = surface,
      .minImageCount = 2,                       // Double buffering
      .imageFormat = VK_FORMAT_B8G8R8A8_UNORM,  // Simplification
      .imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR,
      .imageExtent =
          {
              .width = 800,  // Simplification: Fixed size
              .height = 600,
          },
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
  if (m_vulkanContext == nullptr || m_vulkanContext->swapchain == nullptr ||
      m_vulkanContext->device == nullptr) {
    return;
  }
  vkDestroySwapchainKHR(m_vulkanContext->device, m_vulkanContext->swapchain,
                        nullptr);
}

}  // namespace nextgen::engine::rendering::vulkan
