extern "C" {
#include "components/rendering/vulkan/vulkan_operations.h"
}

int main() {
  vulkan_init();
  vulkan_create_device();
  vulkan_create_swapchain();
  vulkan_cleanup();
}
