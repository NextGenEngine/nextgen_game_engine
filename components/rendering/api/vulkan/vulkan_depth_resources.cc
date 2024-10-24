#include "components/rendering/api/vulkan/vulkan_depth_resources.h"

#include <vulkan/vulkan_core.h>

#include <cstdint>
#include <iostream>
#include <stdexcept>

#include "components/rendering/api/vulkan/vulkan_context.h"
#include "components/rendering/api/vulkan/vulkan_device.hh"

namespace nextgen::engine::rendering::vulkan {

VulkanDepthResources::VulkanDepthResources(VulkanContext& vulkan_context,
                                           VulkanDevice& vulkan_device)
    : vulkan_context_(vulkan_context), vulkan_device_(vulkan_device) {
  std::cout << "VulkanDepthResources object instantiated\n";
}

VulkanDepthResources::~VulkanDepthResources() {
  std::cout << "VulkanDepthResources instance destroyed\n";
}

void VulkanDepthResources::Initialize() { CreateDepthResources(); }

void VulkanDepthResources::Shutdown() const noexcept {
  if (vulkan_context_.device != VK_NULL_HANDLE) {
    if (vulkan_context_.depth_image_view != VK_NULL_HANDLE) {
      vkDestroyImageView(vulkan_context_.device,
                         vulkan_context_.depth_image_view, nullptr);
      vulkan_context_.depth_image_view = VK_NULL_HANDLE;
    } else {
      std::cout << "VulkanDepthResources: depth_image_view does not "
                   "exist. No need to destroy it\n";
    }
    if (vulkan_context_.depth_image != VK_NULL_HANDLE) {
      vkDestroyImage(vulkan_context_.device, vulkan_context_.depth_image,
                     nullptr);
      vulkan_context_.depth_image = VK_NULL_HANDLE;
    } else {
      std::cout << "VulkanDepthResources: depth_image does not "
                   "exist. No need to destroy it\n";
    }
    if (vulkan_context_.depth_image_memory != VK_NULL_HANDLE) {
      vkFreeMemory(vulkan_context_.device, vulkan_context_.depth_image_memory,
                   nullptr);
      vulkan_context_.depth_image_memory = VK_NULL_HANDLE;
    } else {
      std::cout << "VulkanDepthResources: depth_image_memory does not "
                   "exist. No need to destroy it\n";
    }
    // Clear the command buffers vector to avoid dangling references
    vulkan_context_.command_buffers.clear();
  } else {
    std::cout << "VulkanDepthResources: device does not exist. Cannot "
                 "destroy command pool\n";
  }
  std::cout << "VulkanDepthResources: shutdown complete\n";
}

void VulkanDepthResources::CreateDepthResources() {
  VkFormat const depthFormat = vulkan_device_.findDepthFormat();

  CreateImage(vulkan_context_.swap_chain_extent.width,
              vulkan_context_.swap_chain_extent.height, depthFormat,
              VK_IMAGE_TILING_OPTIMAL,
              VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
              VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vulkan_context_.depth_image,
              vulkan_context_.depth_image_memory);

  vulkan_context_.depth_image_view = vulkan_device_.CreateImageView(
      vulkan_context_.depth_image, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT);
}

// NOLINTBEGIN(bugprone-easily-swappable-parameters)
void VulkanDepthResources::CreateImage(uint32_t width, uint32_t height,
                                       VkFormat format, VkImageTiling tiling,
                                       VkImageUsageFlags usage,
                                       VkMemoryPropertyFlags properties,
                                       VkImage& image,
                                       VkDeviceMemory& imageMemory) const {
  // NOLINTEND(bugprone-easily-swappable-parameters)
  VkImageCreateInfo imageInfo{};
  imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
  imageInfo.imageType = VK_IMAGE_TYPE_2D;
  imageInfo.extent.width = width;
  imageInfo.extent.height = height;
  imageInfo.extent.depth = 1;
  imageInfo.mipLevels = 1;
  imageInfo.arrayLayers = 1;
  imageInfo.format = format;
  imageInfo.tiling = tiling;
  imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  imageInfo.usage = usage;
  imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
  imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

  if (vkCreateImage(vulkan_context_.device, &imageInfo, nullptr, &image) !=
      VK_SUCCESS) {
    throw std::runtime_error("failed to create image!");
  }

  VkMemoryRequirements memRequirements;
  vkGetImageMemoryRequirements(vulkan_context_.device, image, &memRequirements);

  VkMemoryAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  allocInfo.allocationSize = memRequirements.size;
  allocInfo.memoryTypeIndex =
      vulkan_device_.FindMemoryType(memRequirements.memoryTypeBits, properties);

  if (vkAllocateMemory(vulkan_context_.device, &allocInfo, nullptr,
                       &imageMemory) != VK_SUCCESS) {
    throw std::runtime_error("failed to allocate image memory!");
  }

  vkBindImageMemory(vulkan_context_.device, image, imageMemory, 0);
}

}  // namespace nextgen::engine::rendering::vulkan
