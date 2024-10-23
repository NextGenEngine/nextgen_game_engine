#include "components/rendering/api/vulkan/vulkan_swapchain.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan_core.h>

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

#include "components/rendering/api/vulkan/vulkan_context.h"
#include "components/rendering/api/vulkan/vulkan_device.hh"
#include "components/rendering/api/vulkan/vulkan_swapchain_types.h"

namespace nextgen::engine::rendering::vulkan {

void VulkanSwapChain::Initialize(VulkanContext& vulkan_context,
                                 VulkanDevice& vulkan_device) {
  vulkan_context_ = &vulkan_context;
  vulkan_device_ = &vulkan_device;
  CreateSwapChain();
  CreateImageViews();
  vulkan_depth_resources_.Initialize(vulkan_context, vulkan_device);
  vulkan_frame_buffers_.Initialize(vulkan_context);
}

void VulkanSwapChain::Shutdown() const noexcept {
  vulkan_depth_resources_.Shutdown();
  vulkan_frame_buffers_.Shutdown();

  if (vulkan_context_ == nullptr || vulkan_context_->device == nullptr) {
    std::cout << "VulkanSwapChain: Vulkan context or device is null; no need "
                 "to cleanup swapchain\n";
    std::cout << "VulkanSwapChain: shutdown complete\n";
    return;
  }

  for (auto* imageView : vulkan_context_->swap_chain_image_views) {
    vkDestroyImageView(vulkan_context_->device, imageView, nullptr);
    std::cout << "VulkanSwapChain: swap_chain_image_views[" << imageView
              << "] destroyed\n";
  }

  if (vulkan_context_->swapchain != VK_NULL_HANDLE) {
    vkDestroySwapchainKHR(vulkan_context_->device, vulkan_context_->swapchain,
                          nullptr);
    vulkan_context_->swapchain = VK_NULL_HANDLE;
    std::cout << "VulkanSwapChain: swapchain destroyed\n";
  } else {
    std::cout << "VulkanSwapChain: swapchain is null; no need to "
                 "destroy it\n";
  }

  std::cout << "VulkanSwapChain: shutdown complete\n";
}

void VulkanSwapChain::CreateSwapChain() {
  SwapChainSupportDetails const swapChainSupport =
      querySwapChainSupport(vulkan_context_->physical_device);

  VkSurfaceFormatKHR const surfaceFormat =
      chooseSwapSurfaceFormat(swapChainSupport.formats);
  VkPresentModeKHR const presentMode =
      chooseSwapPresentMode(swapChainSupport.presentModes);
  VkExtent2D const extent = chooseSwapExtent(swapChainSupport.capabilities);

  uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
  if (swapChainSupport.capabilities.maxImageCount > 0 &&
      imageCount > swapChainSupport.capabilities.maxImageCount) {
    imageCount = swapChainSupport.capabilities.maxImageCount;
  }

  VkSwapchainCreateInfoKHR createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  createInfo.surface = vulkan_context_->surface;

  createInfo.minImageCount = imageCount;
  createInfo.imageFormat = surfaceFormat.format;
  createInfo.imageColorSpace = surfaceFormat.colorSpace;
  createInfo.imageExtent = extent;
  createInfo.imageArrayLayers = 1;
  createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

  QueueFamilyIndices indices =
      vulkan_device_->findQueueFamilies(vulkan_context_->physical_device);
  // NOLINTBEGIN(modernize-avoid-c-arrays,cppcoreguidelines-avoid-c-arrays,bugprone-unchecked-optional-access)
  uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(),
                                   indices.presentFamily.value()};
  // NOLINTEND(modernize-avoid-c-arrays,cppcoreguidelines-avoid-c-arrays,bugprone-unchecked-optional-access)

  if (indices.graphicsFamily != indices.presentFamily) {
    createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
    createInfo.queueFamilyIndexCount = 2;
    createInfo.pQueueFamilyIndices = queueFamilyIndices;
  } else {
    createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
  }

  createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
  createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
  createInfo.presentMode = presentMode;
  createInfo.clipped = VK_TRUE;

  if (vkCreateSwapchainKHR(vulkan_context_->device, &createInfo, nullptr,
                           &vulkan_context_->swapchain) != VK_SUCCESS) {
    throw std::runtime_error("failed to create swap chain!");
  }

  vkGetSwapchainImagesKHR(vulkan_context_->device, vulkan_context_->swapchain,
                          &imageCount, nullptr);
  vulkan_context_->swap_chain_images.resize(imageCount);
  vkGetSwapchainImagesKHR(vulkan_context_->device, vulkan_context_->swapchain,
                          &imageCount,
                          vulkan_context_->swap_chain_images.data());

  vulkan_context_->swap_chain_image_format = surfaceFormat.format;
  vulkan_context_->swap_chain_extent = extent;
}

SwapChainSupportDetails VulkanSwapChain::querySwapChainSupport(
    VkPhysicalDevice device) const {
  SwapChainSupportDetails details;

  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, vulkan_context_->surface,
                                            &details.capabilities);

  uint32_t formatCount = 0;
  vkGetPhysicalDeviceSurfaceFormatsKHR(device, vulkan_context_->surface,
                                       &formatCount, nullptr);

  if (formatCount != 0) {
    details.formats.resize(formatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, vulkan_context_->surface,
                                         &formatCount, details.formats.data());
  }

  uint32_t presentModeCount = 0;
  vkGetPhysicalDeviceSurfacePresentModesKHR(device, vulkan_context_->surface,
                                            &presentModeCount, nullptr);

  if (presentModeCount != 0) {
    details.presentModes.resize(presentModeCount);
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, vulkan_context_->surface,
                                              &presentModeCount,
                                              details.presentModes.data());
  }

  return details;
}

VkSurfaceFormatKHR VulkanSwapChain::chooseSwapSurfaceFormat(
    const std::vector<VkSurfaceFormatKHR>& availableFormats) {
  for (const auto& availableFormat : availableFormats) {
    if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB &&
        availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
      return availableFormat;
    }
  }

  return availableFormats[0];
}

VkPresentModeKHR VulkanSwapChain::chooseSwapPresentMode(
    const std::vector<VkPresentModeKHR>& availablePresentModes) {
  for (const auto& availablePresentMode : availablePresentModes) {
    if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
      return availablePresentMode;
    }
  }

  return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D VulkanSwapChain::chooseSwapExtent(
    const VkSurfaceCapabilitiesKHR& capabilities) const {
  if (capabilities.currentExtent.width !=
      std::numeric_limits<uint32_t>::max()) {
    return capabilities.currentExtent;
  }
  int width = 0;
  int height = 0;
  glfwGetFramebufferSize(vulkan_context_->window, &width, &height);

  VkExtent2D actualExtent = {static_cast<uint32_t>(width),
                             static_cast<uint32_t>(height)};

  actualExtent.width =
      std::clamp(actualExtent.width, capabilities.minImageExtent.width,
                 capabilities.maxImageExtent.width);
  actualExtent.height =
      std::clamp(actualExtent.height, capabilities.minImageExtent.height,
                 capabilities.maxImageExtent.height);

  return actualExtent;
}

void VulkanSwapChain::CreateImageViews() const {
  vulkan_context_->swap_chain_image_views.resize(
      vulkan_context_->swap_chain_images.size());

  for (uint32_t i = 0; i < vulkan_context_->swap_chain_images.size(); i++) {
    vulkan_context_->swap_chain_image_views[i] =
        vulkan_device_->CreateImageView(
            vulkan_context_->swap_chain_images[i],
            vulkan_context_->swap_chain_image_format,
            VK_IMAGE_ASPECT_COLOR_BIT);
  }
}

VulkanSwapChain::~VulkanSwapChain() {
  std::cout << "VulkanSwapChain instance destroyed\n";
}

}  // namespace nextgen::engine::rendering::vulkan
