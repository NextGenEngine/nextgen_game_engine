#include "vulkan_rendering.h"

#include <GLFW/glfw3.h>
#include <vulkan/vulkan_core.h>

#include <iostream>
#include <vector>

#include "components/rendering/api/vulkan/vulkan_config.h"

namespace nextgen::engine::rendering::vulkan {

void VulkanRenderingApi::Initialize() {
  vulkan_instance_.Initialize(vulkan_context_);
  vulkan_validation_layers_.Initialize(vulkan_context_);
  m_vulkan_device.Initialize(vulkan_context_, vulkan_config_);
  m_vulkan_swap_chain.Initialize(vulkan_context_);
  vulkan_buffer_.Initialize(vulkan_context_);
  vulkan_command_pool_.Initialize(vulkan_context_);
  vulkan_frame_buffers_.Initialize(vulkan_context_);
  graphics_pipeline_.Initialize(vulkan_context_);
  vulkan_render_pass_.Initialize(vulkan_context_);
}

void VulkanRenderingApi::StartUp() {
  vulkan_instance_.StartUp();
  vulkan_validation_layers_.StartUp();
}

VkFormat chooseSwapSurfaceFormat(
    const std::vector<VkSurfaceFormatKHR>& availableFormats) {
  for (const auto& availableFormat : availableFormats) {
    if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM &&
        availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
      return availableFormat.format;
    }
  }

  // If VK_FORMAT_B8G8R8A8_UNORM is not available, settle for the first format
  // that is specified
  return availableFormats[0].format;
}

std::vector<VkSurfaceFormatKHR> getSupportedSurfaceFormats(
    VkPhysicalDevice physicalDevice, VkSurfaceKHR surface) {
  uint32_t formatCount;
  vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount,
                                       nullptr);

  std::vector<VkSurfaceFormatKHR> surfaceFormats(formatCount);
  if (formatCount != 0) {
    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount,
                                         surfaceFormats.data());
  }

  return surfaceFormats;
}

void VulkanRenderingApi::Shutdown() {
  vulkan_validation_layers_.Shutdown();
  vulkan_instance_.Shutdown();
}

void VulkanRenderingApi::ApplyConfiguration(const void* config) {
  return;
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-cstyle-cast,google-readability-casting)
  const auto* vulkan_config = (VulkanConfig*)config;
  std::cout << vulkan_config->device_id << "\n";

  m_vulkan_device.CreateDevice();
  m_vulkan_swap_chain.CreateSwapChain();

  vulkan_buffer_.createVertexBuffer(vulkan_context_.device,
                                    vulkan_context_.physical_device);
  graphics_pipeline_.createGraphicsPipeline(vulkan_context_.device);
  auto swapChainImageFormat =
      chooseSwapSurfaceFormat(getSupportedSurfaceFormats(
          vulkan_context_.physical_device, vulkan_context_.surface));
  vulkan_render_pass_.createRenderPass(vulkan_context_.device,
                                       swapChainImageFormat);
  vulkan_frame_buffers_.createFramebuffers(
      vulkan_context_.device, vulkan_context_.swapChainExtent,
      vulkan_context_.swapchain, swapChainImageFormat,
      vulkan_context_.renderPass);

  auto queueFamilyIndex = vulkan_command_pool_.findGraphicsQueueFamilyIndex(
      vulkan_context_.physical_device);
  auto* pool = vulkan_command_pool_.createCommandPool(vulkan_context_.device,
                                                      queueFamilyIndex);
  vulkan_command_pool_.createCommandBuffers(vulkan_context_.device, pool,
                                            vulkan_context_.swapChainExtent);

  createSyncObjects();
}

void VulkanRenderingApi::createSyncObjects() {
  VkSemaphoreCreateInfo semaphoreInfo{};
  semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

  VkFenceCreateInfo fenceInfo{};
  fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;  // Initial state to signaled

  if (vkCreateSemaphore(vulkan_context_.device, &semaphoreInfo, nullptr,
                        &vulkan_context_.imageAvailableSemaphore) !=
          VK_SUCCESS ||
      vkCreateSemaphore(vulkan_context_.device, &semaphoreInfo, nullptr,
                        &vulkan_context_.renderFinishedSemaphore) !=
          VK_SUCCESS ||
      vkCreateFence(vulkan_context_.device, &fenceInfo, nullptr,
                    &vulkan_context_.inFlightFence) != VK_SUCCESS) {
    throw std::runtime_error(
        "Failed to create synchronization objects for a frame");
  }
}

bool VulkanRenderingApi::Exiting() {
  return glfwWindowShouldClose(vulkan_context_.window) != 0;
}

void VulkanRenderingApi::Render() {
  glfwPollEvents();
  // while (glfwWindowShouldClose(vulkan_context_.window) == 0) {
  //   glfwPollEvents();
  // }
  return;
  drawFrame(vulkan_context_.device, vulkan_context_.graphics_queue,
            vulkan_context_.swapchain, vulkan_context_.imageAvailableSemaphore,
            vulkan_context_.renderFinishedSemaphore,
            vulkan_context_.inFlightFence, vulkan_context_.commandBuffers);
}

void VulkanRenderingApi::drawFrame(
    VkDevice device, VkQueue graphicsQueue, VkSwapchainKHR swapChain,
    VkSemaphore imageAvailableSemaphore, VkSemaphore renderFinishedSemaphore,
    VkFence inFlightFence, std::vector<VkCommandBuffer> commandBuffers) {
  uint32_t imageIndex;
  vkAcquireNextImageKHR(device, swapChain, UINT64_MAX, imageAvailableSemaphore,
                        VK_NULL_HANDLE, &imageIndex);

  VkSubmitInfo submitInfo{};
  submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

  VkSemaphore waitSemaphores[] = {imageAvailableSemaphore};
  VkPipelineStageFlags waitStages[] = {
      VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
  submitInfo.waitSemaphoreCount = 1;
  submitInfo.pWaitSemaphores = waitSemaphores;
  submitInfo.pWaitDstStageMask = waitStages;

  submitInfo.commandBufferCount = 1;
  submitInfo.pCommandBuffers = &commandBuffers[imageIndex];

  VkSemaphore signalSemaphores[] = {renderFinishedSemaphore};
  submitInfo.signalSemaphoreCount = 1;
  submitInfo.pSignalSemaphores = signalSemaphores;

  vkWaitForFences(device, 1, &inFlightFence, VK_TRUE, UINT64_MAX);
  vkResetFences(device, 1, &inFlightFence);

  if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, inFlightFence) !=
      VK_SUCCESS) {
    throw std::runtime_error("failed to submit draw command buffer!");
  }

  VkPresentInfoKHR presentInfo{};
  presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
  presentInfo.waitSemaphoreCount = 1;
  presentInfo.pWaitSemaphores = signalSemaphores;

  VkSwapchainKHR swapChains[] = {swapChain};
  presentInfo.swapchainCount = 1;
  presentInfo.pSwapchains = swapChains;
  presentInfo.pImageIndices = &imageIndex;

  vkQueuePresentKHR(graphicsQueue, &presentInfo);
}

VulkanRenderingApi::~VulkanRenderingApi() = default;

}  // namespace nextgen::engine::rendering::vulkan
