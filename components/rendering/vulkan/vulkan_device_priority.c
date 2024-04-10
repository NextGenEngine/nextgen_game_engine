#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <vulkan/vulkan_core.h>

typedef struct {
  uint32_t index;
  const VkPhysicalDeviceProperties* device_properties;
} IndexWithValueWrapper;

// Function to determine priority of a device
int getDevicePriority(const IndexWithValueWrapper* wrapped_index) {
  switch (wrapped_index->device_properties->deviceType) {
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
  const IndexWithValueWrapper* device_a = (const IndexWithValueWrapper*)first;
  const IndexWithValueWrapper* device_b = (const IndexWithValueWrapper*)second;

  int priorityA = getDevicePriority(device_a);
  int priorityB = getDevicePriority(device_b);

  return priorityA - priorityB;
}

// Function to sort device indices by priority
void sortDevicesByPriority(const VkPhysicalDeviceProperties* device_properties,
                           uint32_t device_count, uint32_t* device_indices) {
  // Create an array of indices
  IndexWithValueWrapper wrapped_indexes[device_count];
  for (int i = 0; i < device_count; ++i) {
    wrapped_indexes[i].index = i;
    wrapped_indexes[i].device_properties = &device_properties[i];
  }

  // Sort the indices array based on device priority
  qsort(&wrapped_indexes, device_count, sizeof(IndexWithValueWrapper),
        compareDevices);

  for (int i = 0; i < device_count; ++i) {
    device_indices[i] = wrapped_indexes[i].index;
  }
}
