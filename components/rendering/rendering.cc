extern "C" {
#include "components/rendering/vulkan/vulkan_operations.h"
}

#include "components/configuration/config_manager.h"
#include "rendering.h"

int main() {
  vulkan_init();
  vulkan_create_device();
  vulkan_create_swapchain();
  enumerateAvailableDevices();
  vulkan_cleanup();
}
