#ifndef NEXTGEN_ENGINE_RENDERING_VULKAN_TEXTURE_IMAGE_H
#define NEXTGEN_ENGINE_RENDERING_VULKAN_TEXTURE_IMAGE_H

#include "components/rendering/api/vulkan/vulkan_buffer.h"
#include "components/rendering/api/vulkan/vulkan_command_buffers.h"
#include "components/rendering/api/vulkan/vulkan_context.h"
#include "components/rendering/api/vulkan/vulkan_device.hh"

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)
namespace nextgen::engine::rendering::vulkan {

struct VulkanTextureImage {
  VulkanContext& vulkan_context_;
  VulkanDevice& vulkan_device_;
  VulkanCommandBuffers& vulkan_command_buffers_;
  VulkanBuffer& vulkan_buffer_;

  explicit VulkanTextureImage(VulkanContext& vulkan_context,
                              VulkanDevice& vulkan_device,
                              VulkanCommandBuffers& vulkan_command_buffers,
                              VulkanBuffer& vulkan_buffer);

  void Initialize();
  void Shutdown() const noexcept;

  ~VulkanTextureImage();

  // copy
  VulkanTextureImage& operator=(const VulkanTextureImage&) = delete;
  VulkanTextureImage(const VulkanTextureImage&) = delete;
  // move
  VulkanTextureImage& operator=(VulkanTextureImage&&) = delete;
  VulkanTextureImage(VulkanTextureImage&&) = default;

  struct ImageUsage {
    VkImageUsageFlags flags;
  };

  struct ImageSize {
    uint32_t width;
    uint32_t height;
  };

 private:
  void CreateTextureImage();
  void CreateTextureImageView() const;
  void CreateTextureSampler() const;
  void CreateImage(ImageSize image_size, VkFormat format, VkImageTiling tiling,
                   ImageUsage image_usage,
                   VulkanBuffer::MemoryProperty memory_property, VkImage& image,
                   VkDeviceMemory& imageMemory) const;
  void TransitionImageLayout(VkImage image, VkImageLayout oldLayout,
                             VkImageLayout newLayout) const;
  void CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width,
                         uint32_t height) const;
};

}  // namespace nextgen::engine::rendering::vulkan
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)

#endif
