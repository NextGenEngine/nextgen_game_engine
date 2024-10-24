#include "components/rendering/api/vulkan/vulkan_descriptor_pool.h"

#include <vulkan/vulkan_core.h>

#include <array>
#include <cstdint>
#include <iostream>
#include <stdexcept>

#include "components/rendering/api/vulkan/vulkan_constants.h"
#include "components/rendering/api/vulkan/vulkan_context.h"

namespace nextgen::engine::rendering::vulkan {

VulkanDescriptorPool::VulkanDescriptorPool(VulkanContext& vulkan_context)
    : vulkan_context_(vulkan_context) {
  std::cout << "VulkanDescriptorPool object instantiated\n";
}

VulkanDescriptorPool::~VulkanDescriptorPool() {
  std::cout << "VulkanDescriptorPool instance destroyed\n";
}

void VulkanDescriptorPool::Initialize() { CreateDescriptorPool(); }

void VulkanDescriptorPool::Shutdown() const noexcept {
  if (vulkan_context_.device == nullptr) {
    std::cout
        << "VulkanDescriptorPool: Vulkan context or device is null; no need "
           "to cleanup descriptor pool\n";
    std::cout << "VulkanDescriptorPool: shutdown complete\n";
    return;
  }

  if (vulkan_context_.descriptor_pool != VK_NULL_HANDLE) {
    vkDestroyDescriptorPool(vulkan_context_.device,
                            vulkan_context_.descriptor_pool, nullptr);
    vulkan_context_.descriptor_pool = VK_NULL_HANDLE;
    std::cout << "VulkanDescriptorPool: descriptor_pool destroyed\n";
  } else {
    std::cout << "VulkanDescriptorPool: descriptor_pool is null; no "
                 "need to destroy it\n";
  }

  std::cout << "VulkanDescriptorPool: shutdown complete\n";
}

void VulkanDescriptorPool::CreateDescriptorPool() const {
  std::array<VkDescriptorPoolSize, 2> poolSizes{};
  poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  poolSizes[0].descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
  poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  poolSizes[1].descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

  VkDescriptorPoolCreateInfo poolInfo{};
  poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
  poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
  poolInfo.pPoolSizes = poolSizes.data();
  poolInfo.maxSets = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

  if (vkCreateDescriptorPool(vulkan_context_.device, &poolInfo, nullptr,
                             &vulkan_context_.descriptor_pool) != VK_SUCCESS) {
    throw std::runtime_error("failed to create descriptor pool!");
  }
}

}  // namespace nextgen::engine::rendering::vulkan
