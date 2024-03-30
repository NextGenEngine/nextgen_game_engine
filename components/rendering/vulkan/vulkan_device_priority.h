#ifndef NEXTGEN_ENGINE_VULKAN_DEVICE_PRIORITY_H
#define NEXTGEN_ENGINE_VULKAN_DEVICE_PRIORITY_H

#include <vulkan/vulkan_core.h>

void sortDevicesByPriority(const VkPhysicalDeviceProperties* deviceProperties,
                           uint32_t deviceCount, uint32_t* deviceIndices);

#endif
