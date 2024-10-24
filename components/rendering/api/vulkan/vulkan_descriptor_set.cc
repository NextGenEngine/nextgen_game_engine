#include "components/rendering/api/vulkan/vulkan_descriptor_set.h"

#include <vulkan/vulkan_core.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "components/rendering/api/vulkan/vulkan_constants.h"
#include "components/rendering/api/vulkan/vulkan_context.h"
#include "components/rendering/api/vulkan/vulkan_uniform_buffer.h"

namespace nextgen::engine::rendering::vulkan {

VulkanDescriptorSet::VulkanDescriptorSet(VulkanContext& vulkan_context)
    : vulkan_context_(vulkan_context) {
  std::cout << "VulkanDescriptorSet object instantiated\n";
}

VulkanDescriptorSet::~VulkanDescriptorSet() {
  std::cout << "VulkanDescriptorSet instance destroyed\n";
}

void VulkanDescriptorSet::Initialize() { CreateDescriptorSets(); }

void VulkanDescriptorSet::Shutdown() const noexcept {
  if (vulkan_context_.device == nullptr) {
    std::cout
        << "VulkanDescriptorSet: Vulkan context or device is null; no need "
           "to cleanup descriptor set\n";
    std::cout << "VulkanDescriptorSet: shutdown complete\n";
    return;
  }
  std::cout << "VulkanDescriptorSet: shutdown complete\n";
}

void VulkanDescriptorSet::CreateDescriptorSets() const {
  std::vector<VkDescriptorSetLayout> layouts(
      MAX_FRAMES_IN_FLIGHT, vulkan_context_.descriptor_set_layout);
  VkDescriptorSetAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  allocInfo.descriptorPool = vulkan_context_.descriptor_pool;
  allocInfo.descriptorSetCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
  allocInfo.pSetLayouts = layouts.data();

  vulkan_context_.descriptor_sets.resize(MAX_FRAMES_IN_FLIGHT);
  if (vkAllocateDescriptorSets(vulkan_context_.device, &allocInfo,
                               vulkan_context_.descriptor_sets.data()) !=
      VK_SUCCESS) {
    throw std::runtime_error("failed to allocate descriptor sets!");
  }

  for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
    VkDescriptorBufferInfo bufferInfo{};
    bufferInfo.buffer = vulkan_context_.uniform_buffers[i];
    bufferInfo.offset = 0;
    bufferInfo.range = sizeof(VulkanUniformBuffer::UniformBufferObject);

    VkDescriptorImageInfo imageInfo{};
    imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    imageInfo.imageView = vulkan_context_.texture_image_view;
    imageInfo.sampler = vulkan_context_.texture_sampler;

    std::array<VkWriteDescriptorSet, 2> descriptorWrites{};

    descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWrites[0].dstSet = vulkan_context_.descriptor_sets[i];
    descriptorWrites[0].dstBinding = 0;
    descriptorWrites[0].dstArrayElement = 0;
    descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptorWrites[0].descriptorCount = 1;
    descriptorWrites[0].pBufferInfo = &bufferInfo;

    descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWrites[1].dstSet = vulkan_context_.descriptor_sets[i];
    descriptorWrites[1].dstBinding = 1;
    descriptorWrites[1].dstArrayElement = 0;
    descriptorWrites[1].descriptorType =
        VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    descriptorWrites[1].descriptorCount = 1;
    descriptorWrites[1].pImageInfo = &imageInfo;

    vkUpdateDescriptorSets(vulkan_context_.device,
                           static_cast<uint32_t>(descriptorWrites.size()),
                           descriptorWrites.data(), 0, nullptr);
  }
}

}  // namespace nextgen::engine::rendering::vulkan
