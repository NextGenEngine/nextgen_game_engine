#include "vulkan_rendering.h"

#include <array>
#include <cstdint>
#include <cstring>
#include <ext/matrix_clip_space.hpp>
#include <ext/matrix_transform.hpp>
#include <iostream>
#include <stdexcept>
#include <trigonometric.hpp>

#include "components/configuration/config_manager.h"
#include "components/rendering/api/vulkan/vulkan_buffer.h"
#include "components/rendering/api/vulkan/vulkan_constants.h"
#include "components/rendering/api/vulkan/vulkan_uniform_buffer.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan_core.h>

#include <chrono>
#include <vector>

namespace nextgen::engine::rendering::vulkan {

VulkanRenderingApi::VulkanRenderingApi()
    : vulkan_context_(),
      vulkan_instance_(vulkan_context_),
      vulkan_validation_layers_(vulkan_context_),
      vulkan_device_(vulkan_config_, vulkan_context_),
      vulkan_swap_chain_(vulkan_context_, vulkan_device_),
      vulkan_descriptor_set_layout_(vulkan_context_),
      vulkan_buffer_(vulkan_context_, vulkan_device_, vulkan_command_buffers_),
      vulkan_command_pool_(vulkan_context_, vulkan_device_),
      vulkan_frame_buffers_(vulkan_context_),
      vulkan_texture_image_(vulkan_context_, vulkan_device_,
                            vulkan_command_buffers_, vulkan_buffer_),
      graphics_pipeline_(vulkan_context_),
      vulkan_render_pass_(vulkan_context_),
      vulkan_depth_resources_(vulkan_context_, vulkan_device_),
      vulkan_command_buffers_(vulkan_context_),
      vulkan_model_loader_(vulkan_context_),
      vulkan_vertex_buffer_(vulkan_context_, vulkan_buffer_),
      vulkan_index_buffer_(vulkan_context_, vulkan_buffer_),
      vulkan_uniform_buffer_(vulkan_context_, vulkan_buffer_),
      vulkan_descriptor_pool_(vulkan_context_),
      vulkan_descriptor_set_(vulkan_context_),
      vulkan_sync_object_(vulkan_context_) {
  std::cout << "VulkanRenderingApi object created\n";
}

void VulkanRenderingApi::Initialize() {
  // 1. Vulkan Instance and Validation Layers
  vulkan_instance_.Initialize();
  vulkan_validation_layers_.Initialize();
  // 2. Logical Device
  vulkan_device_.Initialize();
  // 3. Swap Chain
  vulkan_swap_chain_.Initialize();
  // 4. Render Pass (Before Depth Resources)
  vulkan_render_pass_.Initialize();
  // 5. Depth Resources
  vulkan_depth_resources_.Initialize();
  // 6. Framebuffers
  vulkan_frame_buffers_.Initialize();
  // 7. Buffers
  vulkan_buffer_.Initialize();
  // 8. Descriptor Set Layout
  vulkan_descriptor_set_layout_.Initialize();
  // 9. Graphics Pipeline
  graphics_pipeline_.Initialize();
  // 10. Command Pool
  vulkan_command_pool_.Initialize();
  // 11. Texture Image and Model Loader
  vulkan_texture_image_.Initialize();
  vulkan_model_loader_.Initialize();
  // 12. Vertex, Index, and Uniform Buffers
  vulkan_vertex_buffer_.Initialize();
  vulkan_index_buffer_.Initialize();
  vulkan_uniform_buffer_.Initialize();
  // 13. Descriptor Pool and Descriptor Sets
  vulkan_descriptor_pool_.Initialize();
  vulkan_descriptor_set_.Initialize();
  // 14. Command Buffers
  vulkan_command_buffers_.Initialize();
  // 15. Synchronization Objects
  vulkan_sync_object_.Initialize();
}

void VulkanRenderingApi::Shutdown() {
  // 1. Synchronization Objects
  vulkan_sync_object_.Shutdown();
  // 2. Command Buffers
  nextgen::engine::rendering::vulkan::VulkanCommandBuffers::Shutdown();
  // 3. Descriptor Sets and Pool
  vulkan_descriptor_set_.Shutdown();
  vulkan_descriptor_pool_.Shutdown();
  // 4. Buffers
  vulkan_uniform_buffer_.Shutdown();
  vulkan_index_buffer_.Shutdown();
  vulkan_vertex_buffer_.Shutdown();
  // 5. Texture and Model Loading
  vulkan_model_loader_.Shutdown();
  vulkan_texture_image_.Shutdown();
  // 6. Command Pool
  vulkan_command_pool_.Shutdown();
  // 7. Graphics Pipeline and Descriptor Set Layout
  graphics_pipeline_.Shutdown();
  vulkan_descriptor_set_layout_.Shutdown();
  // 8. Framebuffers and Depth Resources
  nextgen::engine::rendering::vulkan::VulkanBuffer::Shutdown();
  vulkan_frame_buffers_.Shutdown();
  vulkan_depth_resources_.Shutdown();
  // 9. Render Pass and Swap Chain
  vulkan_render_pass_.Shutdown();
  vulkan_swap_chain_.Shutdown();
  // 10. Logical Device
  vulkan_device_.Shutdown();
  // 11. Validation Layers and Instance
  vulkan_validation_layers_.Shutdown();
  vulkan_instance_.Shutdown();
}

void VulkanRenderingApi::ApplyConfiguration(const VulkanConfig& config) {
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
    RecreateSwapChain();
    return;
  }
  if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
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

  std::array<VkSemaphore, 1> waitSemaphores = {
      vulkan_context_
          .image_available_semaphores[vulkan_context_.current_frame]};
  std::array<VkPipelineStageFlags, 1> waitStages = {
      VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
  submitInfo.waitSemaphoreCount = 1;
  submitInfo.pWaitSemaphores = waitSemaphores.data();
  submitInfo.pWaitDstStageMask = waitStages.data();

  submitInfo.commandBufferCount = 1;
  submitInfo.pCommandBuffers =
      &vulkan_context_.command_buffers[vulkan_context_.current_frame];

  std::array<VkSemaphore, 1> signalSemaphores = {
      vulkan_context_
          .render_finished_semaphores[vulkan_context_.current_frame]};
  submitInfo.signalSemaphoreCount = 1;
  submitInfo.pSignalSemaphores = signalSemaphores.data();

  if (vkQueueSubmit(
          vulkan_context_.graphics_queue, 1, &submitInfo,
          vulkan_context_.in_flight_fences[vulkan_context_.current_frame]) !=
      VK_SUCCESS) {
    throw std::runtime_error("failed to submit draw command buffer!");
  }

  VkPresentInfoKHR presentInfo{};
  presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

  presentInfo.waitSemaphoreCount = 1;
  presentInfo.pWaitSemaphores = signalSemaphores.data();

  std::array<VkSwapchainKHR, 1> swapChains = {vulkan_context_.swapchain};
  presentInfo.swapchainCount = 1;
  presentInfo.pSwapchains = swapChains.data();

  presentInfo.pImageIndices = &imageIndex;

  result = vkQueuePresentKHR(vulkan_context_.present_queue, &presentInfo);

  if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR ||
      vulkan_context_.framebuffer_resized) {
    vulkan_context_.framebuffer_resized = false;
    RecreateSwapChain();
  } else if (result != VK_SUCCESS) {
    throw std::runtime_error("failed to present swap chain image!");
  }

  vulkan_context_.current_frame =
      (vulkan_context_.current_frame + 1) % MAX_FRAMES_IN_FLIGHT;
}

void VulkanRenderingApi::updateUniformBuffer(uint32_t currentImage) {
  static auto startTime = std::chrono::high_resolution_clock::now();

  auto currentTime = std::chrono::high_resolution_clock::now();
  float const time = std::chrono::duration<float, std::chrono::seconds::period>(
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

void VulkanRenderingApi::RecreateSwapChain() {
  int width = 0;
  int height = 0;
  glfwGetFramebufferSize(vulkan_context_.window, &width, &height);
  while (width == 0 || height == 0) {
    glfwGetFramebufferSize(vulkan_context_.window, &width, &height);
    glfwWaitEvents();
  }

  vkDeviceWaitIdle(vulkan_context_.device);

  CleanupSwapChain();

  vulkan_swap_chain_.Initialize();
  vulkan_depth_resources_.Initialize();
  vulkan_frame_buffers_.Initialize();
}

void VulkanRenderingApi::CleanupSwapChain() const {
  vulkan_frame_buffers_.Shutdown();
  vulkan_depth_resources_.Shutdown();
  vulkan_swap_chain_.Shutdown();
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
  renderPassInfo.renderArea.offset = {.x = 0, .y = 0};
  renderPassInfo.renderArea.extent = vulkan_context_.swap_chain_extent;

  std::array<VkClearValue, 2> clearValues{};
  clearValues[0].color = {{0.0F, 0.0F, 0.0F, 1.0F}};
  clearValues[1].depthStencil = {.depth = 1.0F, .stencil = 0};

  renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
  renderPassInfo.pClearValues = clearValues.data();

  vkCmdBeginRenderPass(commandBuffer, &renderPassInfo,
                       VK_SUBPASS_CONTENTS_INLINE);

  vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
                    vulkan_context_.graphics_pipeline);

  VkViewport viewport{};
  viewport.x = 0.0F;
  viewport.y = 0.0F;
  viewport.width = static_cast<float>(vulkan_context_.swap_chain_extent.width);
  viewport.height =
      static_cast<float>(vulkan_context_.swap_chain_extent.height);
  viewport.minDepth = 0.0F;
  viewport.maxDepth = 1.0F;
  vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

  VkRect2D scissor{};
  scissor.offset = {.x = 0, .y = 0};
  scissor.extent = vulkan_context_.swap_chain_extent;
  vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

  std::array<VkBuffer, 1> vertexBuffers = {vulkan_context_.vertex_buffer};
  std::array<VkDeviceSize, 1> offsets = {0};
  vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers.data(),
                         offsets.data());

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
