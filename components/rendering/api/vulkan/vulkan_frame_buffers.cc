#include "components/rendering/api/vulkan/vulkan_frame_buffers.h"

#include <vulkan/vulkan_core.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "components/rendering/api/vulkan/vulkan_context.h"

namespace nextgen::engine::rendering::vulkan {

VulkanFrameBuffers::VulkanFrameBuffers(VulkanContext& vulkan_context)
    : vulkan_context_(vulkan_context) {
  std::cout << "VulkanFrameBuffers object instantiated\n";
}

VulkanFrameBuffers::~VulkanFrameBuffers() {
  std::cout << "VulkanFrameBuffers instance destroyed\n";
}

void VulkanFrameBuffers::Initialize() { CreateFramebuffers(); }

void VulkanFrameBuffers::Shutdown() const noexcept {
  if (vulkan_context_.device == nullptr) {
    std::cout << "VulkanFrameBuffers: Vulkan context or device is null; no "
                 "need to cleanup frame buffers\n";
    std::cout << "VulkanFrameBuffers: shutdown complete\n";
    return;
  }

  // Destroy framebuffers
  for (auto* framebuffer : vulkan_context_.swap_chain_framebuffers) {
    vkDestroyFramebuffer(vulkan_context_.device, framebuffer, nullptr);
    std::cout << "VulkanFrameBuffers: swap_chain_framebuffers[" << framebuffer
              << "] destroyed\n";
  }
  vulkan_context_.swap_chain_framebuffers.clear();
  std::cout << "VulkanFrameBuffers: shutdown complete\n";
}

void VulkanFrameBuffers::CreateFramebuffers() const {
  vulkan_context_.swap_chain_framebuffers.resize(
      vulkan_context_.swap_chain_image_views.size());

  for (size_t i = 0; i < vulkan_context_.swap_chain_image_views.size(); i++) {
    std::array<VkImageView, 2> attachments = {
        vulkan_context_.swap_chain_image_views[i],
        vulkan_context_.depth_image_view};

    VkFramebufferCreateInfo framebufferInfo{};
    framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferInfo.renderPass = vulkan_context_.render_pass;
    framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
    framebufferInfo.pAttachments = attachments.data();
    framebufferInfo.width = vulkan_context_.swap_chain_extent.width;
    framebufferInfo.height = vulkan_context_.swap_chain_extent.height;
    framebufferInfo.layers = 1;

    if (vkCreateFramebuffer(vulkan_context_.device, &framebufferInfo, nullptr,
                            &vulkan_context_.swap_chain_framebuffers[i]) !=
        VK_SUCCESS) {
      throw std::runtime_error("failed to create framebuffer!");
    }
  }
}

}  // namespace nextgen::engine::rendering::vulkan
