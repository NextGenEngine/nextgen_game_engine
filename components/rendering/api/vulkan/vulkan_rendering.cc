#include "vulkan_rendering.h"

#include <cstring>

#include "components/rendering/api/vulkan/vulkan_buffer.h"
#include "components/rendering/api/vulkan/vulkan_constants.h"
#include "components/rendering/api/vulkan/vulkan_uniform_buffer.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan_core.h>

#include <vector>

namespace nextgen::engine::rendering::vulkan {

void VulkanRenderingApi::Initialize() {
  vulkan_instance_.Initialize(vulkan_context_);
  vulkan_validation_layers_.Initialize(vulkan_context_);
  m_vulkan_device.Initialize(vulkan_context_, vulkan_config_);
  m_vulkan_swap_chain.Initialize(vulkan_context_, m_vulkan_device);
  vulkan_command_buffers_.Initialize(vulkan_context_);
  vulkan_buffer_.Initialize(vulkan_context_, m_vulkan_device,
                            vulkan_command_buffers_);
  vulkan_render_pass_.Initialize(vulkan_context_);
  vulkan_descriptor_set_layout_.Initialize(vulkan_context_);
  graphics_pipeline_.Initialize(vulkan_context_);
  vulkan_command_pool_.Initialize(vulkan_context_, m_vulkan_device);
  // vulkan_depth_resources_.Initialize(vulkan_context_, m_vulkan_device);
  // vulkan_frame_buffers_.Initialize(vulkan_context_);
  vulkan_texture_image_.Initialize(vulkan_context_, m_vulkan_device,
                                   vulkan_command_buffers_, vulkan_buffer_);
  vulkan_model_loader_.Initialize(vulkan_context_);
  vulkan_vertex_buffer_.Initialize(vulkan_context_, vulkan_buffer_);
  vulkan_index_buffer_.Initialize(vulkan_context_, vulkan_buffer_);
  vulkan_uniform_buffer_.Initialize(vulkan_context_, vulkan_buffer_);
  vulkan_descriptor_pool_.Initialize(vulkan_context_);
  vulkan_descriptor_set_.Initialize(vulkan_context_);
  vulkan_command_buffers_.CreateCommandBuffers();
  vulkan_sync_object_.Initialize(vulkan_context_);
}

void VulkanRenderingApi::Shutdown() {
  // vulkan_render_pass_.Shutdown();
  vulkan_sync_object_.Shutdown();
  nextgen::engine::rendering::vulkan::VulkanCommandBuffers::Shutdown();
  vulkan_descriptor_set_.Shutdown();
  vulkan_descriptor_pool_.Shutdown();
  vulkan_uniform_buffer_.Shutdown();
  vulkan_index_buffer_.Shutdown();
  vulkan_vertex_buffer_.Shutdown();
  vulkan_model_loader_.Shutdown();
  vulkan_texture_image_.Shutdown();
  // vulkan_frame_buffers_.Shutdown();
  // vulkan_depth_resources_.Shutdown();
  vulkan_command_pool_.Shutdown();
  graphics_pipeline_.Shutdown();
  vulkan_descriptor_set_layout_.Shutdown();
  vulkan_render_pass_.Shutdown();
  nextgen::engine::rendering::vulkan::VulkanBuffer::Shutdown();
  nextgen::engine::rendering::vulkan::VulkanCommandBuffers::Shutdown();
  m_vulkan_swap_chain.Shutdown();
  m_vulkan_device.Shutdown();
  vulkan_validation_layers_.Shutdown();
  vulkan_instance_.Shutdown();
  // graphics_pipeline_.Shutdown();
  // vulkan_frame_buffers_.Shutdown();
  // vulkan_command_pool_.Shutdown();
  // nextgen::engine::rendering::vulkan::VulkanBuffer::Shutdown();
  // m_vulkan_swap_chain.Shutdown();
  // m_vulkan_device.Shutdown();
  // vulkan_validation_layers_.Shutdown();
  // vulkan_instance_.Shutdown();
}

void VulkanRenderingApi::ApplyConfiguration(const void* config) {
  return;
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-cstyle-cast,google-readability-casting)
  // const auto* vulkan_config = (VulkanConfig*)config;
  // std::cout << vulkan_config->device_id << "\n";

  // m_vulkan_device.CreateDevice();
  // m_vulkan_swap_chain.CreateSwapChain();

  // vulkan_buffer_.createVertexBuffer(vulkan_context_.device,
  //                                   vulkan_context_.physical_device);
  // graphics_pipeline_.createGraphicsPipeline(vulkan_context_.device);
  // auto swapChainImageFormat =
  //     chooseSwapSurfaceFormat(getSupportedSurfaceFormats(
  //         vulkan_context_.physical_device, vulkan_context_.surface));
  // vulkan_render_pass_.createRenderPass(vulkan_context_.device,
  //                                      swapChainImageFormat);
  // vulkan_frame_buffers_.createFramebuffers(
  //     vulkan_context_.device, vulkan_context_.swapChainExtent,
  //     vulkan_context_.swapchain, swapChainImageFormat,
  //     vulkan_context_.renderPass);

  // auto queueFamilyIndex = vulkan_command_pool_.findGraphicsQueueFamilyIndex(
  //     vulkan_context_.physical_device);
  // auto* pool = vulkan_command_pool_.createCommandPool(vulkan_context_.device,
  //                                                     queueFamilyIndex);
  // vulkan_command_pool_.createCommandBuffers(vulkan_context_.device, pool,
  //                                           vulkan_context_.swapChainExtent);

  // createSyncObjects();
}

bool VulkanRenderingApi::Exiting() {
  return glfwWindowShouldClose(vulkan_context_.window) != 0;
}

void VulkanRenderingApi::MainLoop() {
  while (!Exiting()) {
    glfwPollEvents();
    drawFrame();
  }

  vkDeviceWaitIdle(vulkan_context_.device);
}

void VulkanRenderingApi::Render() {
  glfwPollEvents();
  drawFrame();
}

void VulkanRenderingApi::drawFrame() {
  vkWaitForFences(
      vulkan_context_.device, 1,
      &vulkan_context_.in_flight_fences[vulkan_context_.current_frame], VK_TRUE,
      UINT64_MAX);

  uint32_t imageIndex{};
  VkResult result = vkAcquireNextImageKHR(
      vulkan_context_.device, vulkan_context_.swapchain, UINT64_MAX,
      vulkan_context_.image_available_semaphores[vulkan_context_.current_frame],
      VK_NULL_HANDLE, &imageIndex);

  if (result == VK_ERROR_OUT_OF_DATE_KHR) {
    recreateSwapChain();
    return;
  } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
    throw std::runtime_error("failed to acquire swap chain image!");
  }

  updateUniformBuffer(vulkan_context_.current_frame);

  vkResetFences(
      vulkan_context_.device, 1,
      &vulkan_context_.in_flight_fences[vulkan_context_.current_frame]);

  vkResetCommandBuffer(
      vulkan_context_.command_buffers[vulkan_context_.current_frame],
      /*VkCommandBufferResetFlagBits*/ 0);
  recordCommandBuffer(
      vulkan_context_.command_buffers[vulkan_context_.current_frame],
      imageIndex);

  VkSubmitInfo submitInfo{};
  submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

  VkSemaphore waitSemaphores[] = {
      vulkan_context_
          .image_available_semaphores[vulkan_context_.current_frame]};
  VkPipelineStageFlags waitStages[] = {
      VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
  submitInfo.waitSemaphoreCount = 1;
  submitInfo.pWaitSemaphores = waitSemaphores;
  submitInfo.pWaitDstStageMask = waitStages;

  submitInfo.commandBufferCount = 1;
  submitInfo.pCommandBuffers =
      &vulkan_context_.command_buffers[vulkan_context_.current_frame];

  VkSemaphore signalSemaphores[] = {
      vulkan_context_
          .render_finished_semaphores[vulkan_context_.current_frame]};
  submitInfo.signalSemaphoreCount = 1;
  submitInfo.pSignalSemaphores = signalSemaphores;

  if (vkQueueSubmit(
          vulkan_context_.graphics_queue, 1, &submitInfo,
          vulkan_context_.in_flight_fences[vulkan_context_.current_frame]) !=
      VK_SUCCESS) {
    throw std::runtime_error("failed to submit draw command buffer!");
  }

  VkPresentInfoKHR presentInfo{};
  presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

  presentInfo.waitSemaphoreCount = 1;
  presentInfo.pWaitSemaphores = signalSemaphores;

  VkSwapchainKHR swapChains[] = {vulkan_context_.swapchain};
  presentInfo.swapchainCount = 1;
  presentInfo.pSwapchains = swapChains;

  presentInfo.pImageIndices = &imageIndex;

  result = vkQueuePresentKHR(vulkan_context_.present_queue, &presentInfo);

  if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR ||
      vulkan_context_.framebuffer_resized) {
    vulkan_context_.framebuffer_resized = false;
    recreateSwapChain();
  } else if (result != VK_SUCCESS) {
    throw std::runtime_error("failed to present swap chain image!");
  }

  vulkan_context_.current_frame =
      (vulkan_context_.current_frame + 1) % MAX_FRAMES_IN_FLIGHT;
}

void VulkanRenderingApi::updateUniformBuffer(uint32_t currentImage) {
  static auto startTime = std::chrono::high_resolution_clock::now();

  auto currentTime = std::chrono::high_resolution_clock::now();
  float time = std::chrono::duration<float, std::chrono::seconds::period>(
                   currentTime - startTime)
                   .count();

  VulkanUniformBuffer::UniformBufferObject ubo{};
  ubo.model = glm::rotate(glm::mat4(1.0F), time * glm::radians(90.0F),
                          glm::vec3(0.0F, 0.0F, 1.0F));
  ubo.view =
      glm::lookAt(glm::vec3(2.0F, 2.0F, 2.0F), glm::vec3(0.0F, 0.0F, 0.0F),
                  glm::vec3(0.0F, 0.0F, 1.0F));
  ubo.proj = glm::perspective(
      glm::radians(45.0F),
      static_cast<float>(vulkan_context_.swap_chain_extent.width) /
          static_cast<float>(vulkan_context_.swap_chain_extent.height),
      0.1F, 10.0F);
  ubo.proj[1][1] *= -1;

  memcpy(vulkan_context_.uniform_buffers_mapped[currentImage], &ubo,
         sizeof(ubo));
}

void VulkanRenderingApi::recreateSwapChain() {
  int width = 0, height = 0;
  glfwGetFramebufferSize(vulkan_context_.window, &width, &height);
  while (width == 0 || height == 0) {
    glfwGetFramebufferSize(vulkan_context_.window, &width, &height);
    glfwWaitEvents();
  }

  vkDeviceWaitIdle(vulkan_context_.device);

  cleanupSwapChain();

  m_vulkan_swap_chain.Initialize(vulkan_context_, m_vulkan_device);
  // vulkan_depth_resources_.Initialize(vulkan_context_, m_vulkan_device);
  // vulkan_frame_buffers_.Initialize(vulkan_context_);
}

void VulkanRenderingApi::cleanupSwapChain() {
  vkDestroyImageView(vulkan_context_.device, vulkan_context_.depth_image_view,
                     nullptr);
  vkDestroyImage(vulkan_context_.device, vulkan_context_.depth_image, nullptr);
  vkFreeMemory(vulkan_context_.device, vulkan_context_.depth_image_memory,
               nullptr);

  for (auto framebuffer : vulkan_context_.swap_chain_framebuffers) {
    vkDestroyFramebuffer(vulkan_context_.device, framebuffer, nullptr);
  }

  for (auto imageView : vulkan_context_.swap_chain_image_views) {
    vkDestroyImageView(vulkan_context_.device, imageView, nullptr);
  }

  vkDestroySwapchainKHR(vulkan_context_.device, vulkan_context_.swapchain,
                        nullptr);
}

void VulkanRenderingApi::recordCommandBuffer(VkCommandBuffer commandBuffer,
                                             uint32_t imageIndex) {
  VkCommandBufferBeginInfo beginInfo{};
  beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

  if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
    throw std::runtime_error("failed to begin recording command buffer!");
  }

  VkRenderPassBeginInfo renderPassInfo{};
  renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  renderPassInfo.renderPass = vulkan_context_.render_pass;
  renderPassInfo.framebuffer =
      vulkan_context_.swap_chain_framebuffers[imageIndex];
  renderPassInfo.renderArea.offset = {0, 0};
  renderPassInfo.renderArea.extent = vulkan_context_.swap_chain_extent;

  std::array<VkClearValue, 2> clearValues{};
  clearValues[0].color = {{0.0f, 0.0f, 0.0f, 1.0f}};
  clearValues[1].depthStencil = {1.0f, 0};

  renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
  renderPassInfo.pClearValues = clearValues.data();

  vkCmdBeginRenderPass(commandBuffer, &renderPassInfo,
                       VK_SUBPASS_CONTENTS_INLINE);

  vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
                    vulkan_context_.graphics_pipeline);

  VkViewport viewport{};
  viewport.x = 0.0f;
  viewport.y = 0.0f;
  viewport.width = (float)vulkan_context_.swap_chain_extent.width;
  viewport.height = (float)vulkan_context_.swap_chain_extent.height;
  viewport.minDepth = 0.0f;
  viewport.maxDepth = 1.0f;
  vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

  VkRect2D scissor{};
  scissor.offset = {0, 0};
  scissor.extent = vulkan_context_.swap_chain_extent;
  vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

  VkBuffer vertexBuffers[] = {vulkan_context_.vertex_buffer};
  VkDeviceSize offsets[] = {0};
  vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);

  vkCmdBindIndexBuffer(commandBuffer, vulkan_context_.index_buffer, 0,
                       VK_INDEX_TYPE_UINT32);

  vkCmdBindDescriptorSets(
      commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
      vulkan_context_.pipeline_layout, 0, 1,
      &vulkan_context_.descriptor_sets[vulkan_context_.current_frame], 0,
      nullptr);

  vkCmdDrawIndexed(commandBuffer,
                   static_cast<uint32_t>(vulkan_context_.indices.size()), 1, 0,
                   0, 0);

  vkCmdEndRenderPass(commandBuffer);

  if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
    throw std::runtime_error("failed to record command buffer!");
  }
}

VulkanRenderingApi::~VulkanRenderingApi() = default;

}  // namespace nextgen::engine::rendering::vulkan
