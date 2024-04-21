#ifndef NEXTGEN_ENGINE_VULKAN_DEVICE_PRIORITY_H
#define NEXTGEN_ENGINE_VULKAN_DEVICE_PRIORITY_H

#include <vulkan/vulkan_core.h>

#ifdef __cplusplus
extern "C" {
#endif

void sortDevicesByPriority(const VkPhysicalDeviceProperties* device_properties,
                           uint32_t device_count, uint32_t* device_indices);

#ifdef __cplusplus
}
#endif

#endif
