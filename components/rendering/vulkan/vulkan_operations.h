#ifdef __cplusplus
extern "C" {
#endif
#ifndef VULKAN_OPERATIONS_H
#define VULKAN_OPERATIONS_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan_core.h>

VkResult vulkan_init();
VkResult enumerateAvailableDevices();
void vulkan_cleanup();
VkResult vulkan_create_device();
VkResult vulkan_create_swapchain();
VkResult vulkan_render();
void getRecommendedResolutionForDevice();

// Calculated values
extern VkPhysicalDevice *devices;
extern VkPhysicalDeviceProperties *devicesProperties;
extern uint32_t *prioritizedIndexes;
extern uint32_t deviceCount;
extern const GLFWvidmode *glfw_currentVideoMode;

#endif  // VULKAN_OPERATIONS_H

#ifdef __cplusplus
}
#endif
