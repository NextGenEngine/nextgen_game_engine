#include "components/rendering/api/vulkan/vulkan_texture_image.h"

#include <vulkan/vulkan_core.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>

#include "components/rendering/api/vulkan/vulkan_buffer.h"
#include "components/rendering/api/vulkan/vulkan_command_buffers.h"
#include "components/rendering/api/vulkan/vulkan_context.h"
#include "components/rendering/api/vulkan/vulkan_device.hh"

#define STB_IMAGE_IMPLEMENTATION
#include "third_party/stb/stb_image.h"

namespace nextgen::engine::rendering::vulkan {

const std::string TEXTURE_PATH = "data/textures/viking_room.png";

VulkanTextureImage::VulkanTextureImage(
    VulkanContext& vulkan_context, VulkanDevice& vulkan_device,
    VulkanCommandBuffers& vulkan_command_buffers, VulkanBuffer& vulkan_buffer)
    : vulkan_context_(vulkan_context),
      vulkan_device_(vulkan_device),
      vulkan_command_buffers_(vulkan_command_buffers),
      vulkan_buffer_(vulkan_buffer) {
  std::cout << "VulkanTextureImage object instantiated\n";
}

VulkanTextureImage::~VulkanTextureImage() {
  std::cout << "VulkanTextureImage instance destroyed\n";
}

void VulkanTextureImage::Initialize() {
  CreateTextureImage();
  CreateTextureImageView();
  CreateTextureSampler();
}

void VulkanTextureImage::Shutdown() const noexcept {
  if (vulkan_context_.device == nullptr) {
    std::cout
        << "VulkanTextureImage: Vulkan context or device is null; no need "
           "to cleanup swapchain\n";
    std::cout << "VulkanTextureImage: shutdown complete\n";
    return;
  }

  if (vulkan_context_.texture_sampler != VK_NULL_HANDLE) {
    vkDestroySampler(vulkan_context_.device, vulkan_context_.texture_sampler,
                     nullptr);
    vulkan_context_.texture_sampler = VK_NULL_HANDLE;
    std::cout << "VulkanTextureImage: texture_sampler destroyed\n";
  } else {
    std::cout << "VulkanTextureImage: texture_sampler does not exist. No "
                 "reason to destroy it\n";
  }

  if (vulkan_context_.texture_image_view != VK_NULL_HANDLE) {
    vkDestroyImageView(vulkan_context_.device,
                       vulkan_context_.texture_image_view, nullptr);
    vulkan_context_.texture_image_view = VK_NULL_HANDLE;
    std::cout << "VulkanTextureImage: texture_image_view destroyed\n";
  } else {
    std::cout << "VulkanTextureImage: texture_image_view does not exist. No "
                 "reason to destroy it\n";
  }

  if (vulkan_context_.texture_image != VK_NULL_HANDLE) {
    vkDestroyImage(vulkan_context_.device, vulkan_context_.texture_image,
                   nullptr);
    vulkan_context_.texture_image = VK_NULL_HANDLE;
    std::cout << "VulkanTextureImage: texture_image destroyed\n";
  } else {
    std::cout << "VulkanTextureImage: texture_image does not exist. No reason "
                 "to destroy it\n";
  }

  if (vulkan_context_.texture_image_memory != VK_NULL_HANDLE) {
    vkFreeMemory(vulkan_context_.device, vulkan_context_.texture_image_memory,
                 nullptr);
    vulkan_context_.texture_image_memory = VK_NULL_HANDLE;
    std::cout << "VulkanTextureImage: texture_image_memory destroyed\n";
  } else {
    std::cout << "VulkanTextureImage: texture_image_memory does not exist. No "
                 "reason to destroy it\n";
  }

  std::cout << "VulkanTextureImage: shutdown complete\n";
}

void VulkanTextureImage::CreateTextureImage() {
  int texWidth = 0;
  int texHeight = 0;
  int texChannels = 0;
  stbi_uc* pixels = stbi_load(TEXTURE_PATH.c_str(), &texWidth, &texHeight,
                              &texChannels, STBI_rgb_alpha);
  VkDeviceSize const imageSize = static_cast<VkDeviceSize>(texWidth) *
                                 static_cast<VkDeviceSize>(texHeight) *
                                 static_cast<VkDeviceSize>(4);

  if (pixels == nullptr) {
    throw std::runtime_error("failed to load texture image!");
  }

  VkBuffer stagingBuffer{};
  VkDeviceMemory stagingBufferMemory{};
  vulkan_buffer_.CreateBuffer(
      imageSize, VulkanBuffer::BufferUsage{VK_BUFFER_USAGE_TRANSFER_SRC_BIT},
      VulkanBuffer::MemoryProperty{VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                                   VK_MEMORY_PROPERTY_HOST_COHERENT_BIT},
      stagingBuffer, stagingBufferMemory);

  void* data{};
  vkMapMemory(vulkan_context_.device, stagingBufferMemory, 0, imageSize, 0,
              &data);
  memcpy(data, pixels, static_cast<size_t>(imageSize));
  vkUnmapMemory(vulkan_context_.device, stagingBufferMemory);

  stbi_image_free(pixels);

  CreateImage(
      ImageSize{.width = static_cast<uint32_t>(texWidth),
                .height = static_cast<uint32_t>(texHeight)},
      VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_TILING_OPTIMAL,
      ImageUsage{VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT},
      VulkanBuffer::MemoryProperty{VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT},
      vulkan_context_.texture_image, vulkan_context_.texture_image_memory);

  TransitionImageLayout(vulkan_context_.texture_image,
                        VK_IMAGE_LAYOUT_UNDEFINED,
                        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
  CopyBufferToImage(stagingBuffer, vulkan_context_.texture_image,
                    static_cast<uint32_t>(texWidth),
                    static_cast<uint32_t>(texHeight));
  TransitionImageLayout(vulkan_context_.texture_image,
                        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                        VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

  vkDestroyBuffer(vulkan_context_.device, stagingBuffer, nullptr);
  vkFreeMemory(vulkan_context_.device, stagingBufferMemory, nullptr);
}

void VulkanTextureImage::CreateImage(
    ImageSize image_size, VkFormat format, VkImageTiling tiling,
    ImageUsage image_usage, VulkanBuffer::MemoryProperty memory_property,
    VkImage& image, VkDeviceMemory& imageMemory) const {
  VkImageCreateInfo imageInfo{};
  imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
  imageInfo.imageType = VK_IMAGE_TYPE_2D;
  imageInfo.extent.width = image_size.width;
  imageInfo.extent.height = image_size.height;
  imageInfo.extent.depth = 1;
  imageInfo.mipLevels = 1;
  imageInfo.arrayLayers = 1;
  imageInfo.format = format;
  imageInfo.tiling = tiling;
  imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  imageInfo.usage = image_usage.flags;
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
  allocInfo.memoryTypeIndex = vulkan_device_.FindMemoryType(
      memRequirements.memoryTypeBits, memory_property.flags);

  if (vkAllocateMemory(vulkan_context_.device, &allocInfo, nullptr,
                       &imageMemory) != VK_SUCCESS) {
    throw std::runtime_error("failed to allocate image memory!");
  }

  vkBindImageMemory(vulkan_context_.device, image, imageMemory, 0);
}

void VulkanTextureImage::TransitionImageLayout(VkImage image,
                                               VkImageLayout oldLayout,
                                               VkImageLayout newLayout) const {
  VkCommandBuffer commandBuffer =
      vulkan_command_buffers_.BeginSingleTimeCommands();

  VkImageMemoryBarrier barrier{};
  barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
  barrier.oldLayout = oldLayout;
  barrier.newLayout = newLayout;
  barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  barrier.image = image;
  barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  barrier.subresourceRange.baseMipLevel = 0;
  barrier.subresourceRange.levelCount = 1;
  barrier.subresourceRange.baseArrayLayer = 0;
  barrier.subresourceRange.layerCount = 1;

  VkPipelineStageFlags sourceStage{};
  VkPipelineStageFlags destinationStage{};

  if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED &&
      newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
    barrier.srcAccessMask = 0;
    barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

    sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
    destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
  } else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL &&
             newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
    barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

    sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
  } else {
    throw std::invalid_argument("unsupported layout transition!");
  }

  vkCmdPipelineBarrier(commandBuffer, sourceStage, destinationStage, 0, 0,
                       nullptr, 0, nullptr, 1, &barrier);

  vulkan_command_buffers_.EndSingleTimeCommands(commandBuffer);
}

void VulkanTextureImage::CopyBufferToImage(VkBuffer buffer, VkImage image,
                                           uint32_t width,
                                           uint32_t height) const {
  VkCommandBuffer commandBuffer =
      vulkan_command_buffers_.BeginSingleTimeCommands();

  VkBufferImageCopy region{};
  region.bufferOffset = 0;
  region.bufferRowLength = 0;
  region.bufferImageHeight = 0;
  region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  region.imageSubresource.mipLevel = 0;
  region.imageSubresource.baseArrayLayer = 0;
  region.imageSubresource.layerCount = 1;
  region.imageOffset = {.x = 0, .y = 0, .z = 0};
  region.imageExtent = {.width = width, .height = height, .depth = 1};

  vkCmdCopyBufferToImage(commandBuffer, buffer, image,
                         VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

  vulkan_command_buffers_.EndSingleTimeCommands(commandBuffer);
}

void VulkanTextureImage::CreateTextureImageView() const {
  vulkan_context_.texture_image_view = vulkan_device_.CreateImageView(
      vulkan_context_.texture_image, VK_FORMAT_R8G8B8A8_SRGB,
      VK_IMAGE_ASPECT_COLOR_BIT);
}

void VulkanTextureImage::CreateTextureSampler() const {
  VkPhysicalDeviceProperties properties{};
  vkGetPhysicalDeviceProperties(vulkan_context_.physical_device, &properties);

  VkSamplerCreateInfo samplerInfo{};
  samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
  samplerInfo.magFilter = VK_FILTER_LINEAR;
  samplerInfo.minFilter = VK_FILTER_LINEAR;
  samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
  samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
  samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
  samplerInfo.anisotropyEnable = VK_TRUE;
  samplerInfo.maxAnisotropy = properties.limits.maxSamplerAnisotropy;
  samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
  samplerInfo.unnormalizedCoordinates = VK_FALSE;
  samplerInfo.compareEnable = VK_FALSE;
  samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
  samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;

  if (vkCreateSampler(vulkan_context_.device, &samplerInfo, nullptr,
                      &vulkan_context_.texture_sampler) != VK_SUCCESS) {
    throw std::runtime_error("failed to create texture sampler!");
  }
}

}  // namespace nextgen::engine::rendering::vulkan
