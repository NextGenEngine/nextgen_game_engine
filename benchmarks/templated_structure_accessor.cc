struct Vulkan {
  int device_id{5};
};

struct Rendering {
  Vulkan vulkan;
};

static struct Application {
  Rendering rendering;
} app;  // Global instance

template <typename T>
struct Accessor;

// Specialization for Application
template <>
struct Accessor<Application> {
  // Directly expose Vulkan as a static reference
  static Vulkan& vulkan;
};

// You have to define the static member outside the class
Vulkan& Accessor<Application>::vulkan = app.rendering.vulkan;

#define VULKAN app.rendering.vulkan

static auto& VulkanConfig = Accessor<Application>::vulkan;

#include <iostream>

int main() {
  VulkanConfig.device_id += 3;
  std::cout << VulkanConfig.device_id << "\n";
  VulkanConfig.device_id += 8;
  std::cout << app.rendering.vulkan.device_id << "\n";
  return 0;
}
