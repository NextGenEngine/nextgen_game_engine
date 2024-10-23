#include "components/rendering/api/vulkan/vulkan_descriptor_set_layout.h"

#include <vulkan/vulkan_core.h>

#include <array>
#include <cstdint>
#include <iostream>
#include <stdexcept>

#include "components/rendering/api/vulkan/vulkan_context.h"

namespace nextgen::engine::rendering::vulkan {

VulkanDescriptorSetLayout::VulkanDescriptorSetLayout() {
  std::cout << "VulkanDescriptorSetLayout object instantiated\n";
}

VulkanDescriptorSetLayout::~VulkanDescriptorSetLayout() {
  std::cout << "VulkanDescriptorSetLayout instance destroyed\n";
}

void VulkanDescriptorSetLayout::Initialize(VulkanContext& vulkan_context) {
  vulkan_context_ = &vulkan_context;
  CreateDescriptorSetLayout();
}

void VulkanDescriptorSetLayout::Shutdown() const noexcept {
  if (vulkan_context_ == nullptr || vulkan_context_->device == nullptr) {
    std::cout << "VulkanDescriptorSetLayout: Vulkan context or device is null; "
                 "no need "
                 "to cleanup command pool\n";
    std::cout << "VulkanDescriptorSetLayout: shutdown complete\n";
    return;
  }

  if (vulkan_context_->descriptor_set_layout != VK_NULL_HANDLE) {
    vkDestroyDescriptorSetLayout(vulkan_context_->device,
                                 vulkan_context_->descriptor_set_layout,
                                 nullptr);
    vulkan_context_->descriptor_set_layout = VK_NULL_HANDLE;
    std::cout << "VulkanDescriptorSetLayout: descriptor_set_layout destroyed\n";
  } else {
    std::cout << "VulkanDescriptorSetLayout: descriptor_set_layout is null; no "
                 "need to destroy it\n";
  }

  std::cout << "VulkanDescriptorSetLayout: shutdown complete\n";
}

void VulkanDescriptorSetLayout::CreateDescriptorSetLayout() const {
  VkDescriptorSetLayoutBinding uboLayoutBinding{};
  uboLayoutBinding.binding = 0;
  uboLayoutBinding.descriptorCount = 1;
  uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  uboLayoutBinding.pImmutableSamplers = nullptr;
  uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

  VkDescriptorSetLayoutBinding samplerLayoutBinding{};
  samplerLayoutBinding.binding = 1;
  samplerLayoutBinding.descriptorCount = 1;
  samplerLayoutBinding.descriptorType =
      VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  samplerLayoutBinding.pImmutableSamplers = nullptr;
  samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

  std::array<VkDescriptorSetLayoutBinding, 2> bindings = {uboLayoutBinding,
                                                          samplerLayoutBinding};
  VkDescriptorSetLayoutCreateInfo layoutInfo{};
  layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
  layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
  layoutInfo.pBindings = bindings.data();

  if (vkCreateDescriptorSetLayout(vulkan_context_->device, &layoutInfo, nullptr,
                                  &vulkan_context_->descriptor_set_layout) !=
      VK_SUCCESS) {
    throw std::runtime_error("failed to create descriptor set layout!");
  }
}

}  // namespace nextgen::engine::rendering::vulkan
