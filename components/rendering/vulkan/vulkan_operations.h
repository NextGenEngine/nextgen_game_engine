#ifndef VULKAN_OPERATIONS_H
#define VULKAN_OPERATIONS_H

#include <vulkan/vulkan_core.h>

VkResult vulkan_init();
void vulkan_cleanup();
VkResult vulkan_create_device();
VkResult vulkan_create_swapchain();
VkResult vulkan_render();

#endif  // VULKAN_OPERATIONS_H
