/* WARNING!!!
   This file is not used in project anymore. I leave it here as an example of
   implementation in pure C-language (which is 100% binary compatible with
   Vulkan API). It can be used for comparison reasons in case of C++ have some
   issues with types or definitions.
*/

#ifndef VULKAN_OPERATIONS_H
#define VULKAN_OPERATIONS_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan_core.h>

#ifdef __cplusplus
extern "C" {
#endif

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
#ifdef __cplusplus
}
#endif

#endif  // VULKAN_OPERATIONS_H
