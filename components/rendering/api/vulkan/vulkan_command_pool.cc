#include "components/rendering/api/vulkan/vulkan_command_pool.h"

#include <vulkan/vulkan_core.h>

#include <vector>

#include "components/rendering/api/vulkan/vulkan_context.h"

namespace nextgen::engine::rendering::vulkan {

void VulkanCommandPool::Initialize(VulkanContext& vulkan_context) {
  vulkan_context_ = &vulkan_context;
}

struct Vertex {
  float pos[2];
  float color[3];
};

std::vector<Vertex> vertices2 = {
    {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},  // Bottom left
    {{0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},   // Bottom right
    {{0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}},    // Top right
    {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},  // Bottom left
    {{0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}},    // Top right
    {{-0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}}    // Top left
};

void VulkanCommandPool::createCommandBuffers(VkDevice device,
                                             VkCommandPool commandPool,
                                             VkExtent2D swapChainExtent) {
  auto& swapChainFramebuffers = vulkan_context_->swapChainFramebuffers;
  auto& commandBuffers = vulkan_context_->commandBuffers;
  commandBuffers.resize(swapChainFramebuffers.size());

  VkCommandBufferAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocInfo.commandPool = commandPool;
  allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocInfo.commandBufferCount = (uint32_t)commandBuffers.size();

  if (vkAllocateCommandBuffers(device, &allocInfo, commandBuffers.data()) !=
      VK_SUCCESS) {
    throw std::runtime_error("failed to allocate command buffers!");
  }

  for (size_t i = 0; i < commandBuffers.size(); i++) {
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS) {
      throw std::runtime_error("failed to begin recording command buffer!");
    }

    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = vulkan_context_->renderPass;
    renderPassInfo.framebuffer = swapChainFramebuffers[i];
    renderPassInfo.renderArea.offset = {0, 0};
    renderPassInfo.renderArea.extent = swapChainExtent;

    VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues = &clearColor;

    vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo,
                         VK_SUBPASS_CONTENTS_INLINE);

    vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS,
                      vulkan_context_->graphicsPipeline);

    VkBuffer vertexBuffers[] = {vulkan_context_->vertexBuffer};
    VkDeviceSize offsets[] = {0};
    vkCmdBindVertexBuffers(commandBuffers[i], 0, 1, vertexBuffers, offsets);

    vkCmdDraw(commandBuffers[i], static_cast<uint32_t>(vertices2.size()), 1, 0,
              0);

    vkCmdEndRenderPass(commandBuffers[i]);

    if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
      throw std::runtime_error("failed to record command buffer!");
    }
  }
}

uint32_t VulkanCommandPool::findGraphicsQueueFamilyIndex(
    VkPhysicalDevice physicalDevice) {
  uint32_t queueFamilyCount = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount,
                                           nullptr);
  std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
  vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount,
                                           queueFamilies.data());

  for (uint32_t i = 0; i < queueFamilyCount; i++) {
    if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
      return i;
    }
  }

  throw std::runtime_error("Failed to find a suitable queue family!");
}

VkCommandPool VulkanCommandPool::createCommandPool(VkDevice device,
                                                   uint32_t queueFamilyIndex) {
  VkCommandPoolCreateInfo poolInfo{};
  poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  poolInfo.queueFamilyIndex = queueFamilyIndex;
  poolInfo.flags =
      VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;  // Allows command
                                                        // buffers to be
                                                        // individually reset

  VkCommandPool commandPool;
  if (vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool) !=
      VK_SUCCESS) {
    throw std::runtime_error("Failed to create command pool!");
  }

  return commandPool;
}

}  // namespace nextgen::engine::rendering::vulkan
