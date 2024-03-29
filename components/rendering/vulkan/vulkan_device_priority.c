#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <vulkan/vulkan_core.h>

typedef struct {
  uint32_t index;
  const VkPhysicalDeviceProperties* deviceProperties;
} IndexWithValueWrapper;

// Function to determine priority of a device
int getDevicePriority(const IndexWithValueWrapper* wrappedIndex) {
  switch (wrappedIndex->deviceProperties->deviceType) {
    case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
      return 1;
    case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
      return 2;
    case VK_PHYSICAL_DEVICE_TYPE_CPU:
      return 3;
    case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
      return 4;
    case VK_PHYSICAL_DEVICE_TYPE_OTHER:
      return 5;
    default:
      return 6;
  }
}

// Comparison function for qsort
int compareDevices(const void* first, const void* second) {
  const IndexWithValueWrapper* deviceA = (const IndexWithValueWrapper*)first;
  const IndexWithValueWrapper* deviceB = (const IndexWithValueWrapper*)second;

  int priorityA = getDevicePriority(deviceA);
  int priorityB = getDevicePriority(deviceB);

  return priorityA - priorityB;
}

// Function to sort device indices by priority
void sortDevicesByPriority(const VkPhysicalDeviceProperties* deviceProperties,
                           uint32_t deviceCount, uint32_t* deviceIndices) {
  // Create an array of indices
  IndexWithValueWrapper wrappedIndexes[deviceCount];
  for (int i = 0; i < deviceCount; ++i) {
    wrappedIndexes[i].index = i;
    wrappedIndexes[i].deviceProperties = &deviceProperties[i];
  }

  // Sort the indices array based on device priority
  qsort(&wrappedIndexes, deviceCount, sizeof(IndexWithValueWrapper),
        compareDevices);

  for (int i = 0; i < deviceCount; ++i) {
    deviceIndices[i] = wrappedIndexes[i].index;
  }
}
