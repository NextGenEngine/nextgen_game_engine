#include "components/rendering/api/vulkan/vulkan_sync_object.h"

#include <vulkan/vulkan_core.h>

#include <cstddef>
#include <iostream>
#include <stdexcept>

#include "components/rendering/api/vulkan/vulkan_constants.h"
#include "components/rendering/api/vulkan/vulkan_context.h"

namespace nextgen::engine::rendering::vulkan {

VulkanSyncObject::VulkanSyncObject(VulkanContext& vulkan_context)
    : vulkan_context_(vulkan_context) {
  std::cout << "VulkanSyncObject object instantiated\n";
}

VulkanSyncObject::~VulkanSyncObject() {
  std::cout << "VulkanSyncObject instance destroyed\n";
}

void VulkanSyncObject::Initialize() { CreateSyncObjects(); }

void VulkanSyncObject::Shutdown() const noexcept {
  if (vulkan_context_.device == nullptr) {
    std::cout << "VulkanSyncObject: Vulkan context or device is null; no need "
                 "to cleanup swapchain\n";
    std::cout << "VulkanSyncObject: shutdown complete\n";
    return;
  }

  for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
    if (vulkan_context_.render_finished_semaphores[i] != VK_NULL_HANDLE) {
      vkDestroySemaphore(vulkan_context_.device,
                         vulkan_context_.render_finished_semaphores[i],
                         nullptr);
      vulkan_context_.render_finished_semaphores[i] = VK_NULL_HANDLE;
      std::cout << "VulkanSyncObject: render_finished_semaphores[" << i
                << "] destroyed\n";
    } else {
      std::cout << "VulkanSyncObject: render_finished_semaphores[" << i
                << "] is null;  no need to destroy it\n";
    }

    if (vulkan_context_.image_available_semaphores[i] != VK_NULL_HANDLE) {
      vkDestroySemaphore(vulkan_context_.device,
                         vulkan_context_.image_available_semaphores[i],
                         nullptr);
      vulkan_context_.image_available_semaphores[i] = VK_NULL_HANDLE;
      std::cout << "VulkanSyncObject: image_available_semaphores[" << i
                << "] destroyed\n";
    } else {
      std::cout << "VulkanSyncObject: image_available_semaphores[" << i
                << "] is null;  no need to destroy it\n";
    }

    if (vulkan_context_.in_flight_fences[i] != VK_NULL_HANDLE) {
      vkDestroyFence(vulkan_context_.device,
                     vulkan_context_.in_flight_fences[i], nullptr);
      vulkan_context_.in_flight_fences[i] = VK_NULL_HANDLE;
      std::cout << "VulkanSyncObject: in_flight_fences[" << i
                << "] destroyed\n";
    } else {
      std::cout << "VulkanSyncObject: in_flight_fences[" << i
                << "] is null;  no need to destroy it\n";
    }
  }

  std::cout << "VulkanSyncObject: shutdown complete\n";
}

void VulkanSyncObject::CreateSyncObjects() const {
  vulkan_context_.image_available_semaphores.resize(MAX_FRAMES_IN_FLIGHT);
  vulkan_context_.render_finished_semaphores.resize(MAX_FRAMES_IN_FLIGHT);
  vulkan_context_.in_flight_fences.resize(MAX_FRAMES_IN_FLIGHT);

  VkSemaphoreCreateInfo semaphoreInfo{};
  semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

  VkFenceCreateInfo fenceInfo{};
  fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

  for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
    if (vkCreateSemaphore(vulkan_context_.device, &semaphoreInfo, nullptr,
                          &vulkan_context_.image_available_semaphores[i]) !=
            VK_SUCCESS ||
        vkCreateSemaphore(vulkan_context_.device, &semaphoreInfo, nullptr,
                          &vulkan_context_.render_finished_semaphores[i]) !=
            VK_SUCCESS ||
        vkCreateFence(vulkan_context_.device, &fenceInfo, nullptr,
                      &vulkan_context_.in_flight_fences[i]) != VK_SUCCESS) {
      throw std::runtime_error(
          "failed to create synchronization objects for a frame!");
    }
  }
}

}  // namespace nextgen::engine::rendering::vulkan
