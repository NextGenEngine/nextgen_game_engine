#include <vulkan/vulkan_core.h>

void sortDevicesByPriority(const VkPhysicalDeviceProperties* deviceProperties,
                           uint32_t deviceCount, uint32_t* deviceIndices);
