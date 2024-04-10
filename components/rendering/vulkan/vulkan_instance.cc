#include "vulkan_instance.h"

#include <cstdint>
#include <cstdlib>
#include <iostream>

#include "components/rendering/vulkan/vulkan_config.h"
#include "vulkan_context.h"
#include "vulkan_device_priority.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan_core.h>

#include <stdexcept>

namespace nextgen::engine::rendering::vulkan {

using nextgen::engine::rendering::vulkan::VulkanContext;

void enumerateAvailableDevices(VkInstance& instance);
void getRecommendedResolutionForDevice();
const char* GetDeviceTypeName(VkPhysicalDeviceType deviceType);

// Initialize the Vulkan library
VkApplicationInfo appInfo = {
    .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
    .pApplicationName = "NextGen-Game-Engine",
    .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
    .pEngineName = "NextGen-Game-Engine",
    .engineVersion = VK_MAKE_VERSION(1, 0, 0),
    .apiVersion = VK_API_VERSION_1_0,
};

VulkanInstance::VulkanInstance(VulkanContext* vulkan_context)
    : m_vulkan_context(vulkan_context) {
  // Initialize the Vulkan library
  // Initialize GLFW
  auto& window = m_vulkan_context->window;
  auto& instance = m_vulkan_context->instance;
  auto& surface = m_vulkan_context->surface;

  if (glfwInit() == 0) {
    throw std::runtime_error("Failed to initialize GLFW: glfwInit()");
  }

  if (glfwVulkanSupported() == 0) {
    throw std::runtime_error(
        "Vulkan not supported on the system: glfwVulkanSupported()");
  }

  // Specify that we won't be creating an OpenGL context
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  // Create a windowed mode window and its OpenGL context
  vulkan_context->window =
      glfwCreateWindow(800, 600, "Hello Vulkan", nullptr, nullptr);
  if (vulkan_context->window == nullptr) {
    glfwTerminate();
    throw std::runtime_error(
        "Failed to create GLFW window: glfwCreateWindow()");
  }

  uint32_t glfwExtensionCount = 0;
  const char** glfwExtensions = nullptr;
  glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

  const VkInstanceCreateInfo createInfo = {
      .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
      .pApplicationInfo = &appInfo,
      .enabledExtensionCount = glfwExtensionCount,
      .ppEnabledExtensionNames = glfwExtensions,
  };

  if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
    throw std::runtime_error("Failed to create Vulkan instance");
  }

  const VkResult result =
      glfwCreateWindowSurface(instance, window, nullptr, &surface);
  if (result != VK_SUCCESS) {
    throw std::runtime_error("Failed to create window surface");
  }
}

// Calculated values
VkPhysicalDevice* devices = nullptr;
VkPhysicalDeviceProperties* devicesProperties = nullptr;
uint32_t* prioritizedIndexes = nullptr;
uint32_t deviceCount = 0;
const GLFWvidmode* glfw_currentVideoMode = nullptr;

VulkanConfig VulkanInstance::DefaultConfiguration() {
  enumerateAvailableDevices(m_vulkan_context->instance);
  getRecommendedResolutionForDevice();

  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
  const uint32_t defaultDeviceIndex = prioritizedIndexes[0];
  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
  const VkPhysicalDeviceProperties& defaultDeviceProperties = devicesProperties
      [defaultDeviceIndex];  // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
  const auto* currentVideoMode = glfw_currentVideoMode;

  return VulkanConfig{
      .device_id = defaultDeviceProperties.deviceID,
      .width = static_cast<uint32_t>(currentVideoMode->width),
      .height = static_cast<uint32_t>(currentVideoMode->height),
      .refresh_rate = static_cast<float>(currentVideoMode->refreshRate)};
}

void enumerateAvailableDevices(VkInstance& instance) {
  VkResult result = {};

  // Create Vulkan instance
  VkApplicationInfo appInfo = {VK_STRUCTURE_TYPE_APPLICATION_INFO};
  appInfo.pApplicationName = "Vulkan Device Listing";
  appInfo.apiVersion = VK_API_VERSION_1_0;

  VkInstanceCreateInfo createInfo = {VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO};
  createInfo.pApplicationInfo = &appInfo;

  // Enumerate physical devices
  result = vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
  if (result != VK_SUCCESS) {
    throw std::runtime_error("Vulkan: Failed to enumerate physical devices");
  }

  if (deviceCount == 0) {
    throw std::runtime_error("Vulkan: No Vulkan-compatible devices found");
  }

  // Allocate memory for physical devices
  // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
  devices = static_cast<VkPhysicalDevice*>(
      // NOLINTNEXTLINE(cppcoreguidelines-no-malloc)
      malloc(sizeof(VkPhysicalDevice) * deviceCount));
  if (devices == nullptr) {
    throw std::runtime_error("Vulkan: Failed to allocate memory for devices");
  }

  // Retrieve physical devices
  result = vkEnumeratePhysicalDevices(instance, &deviceCount, devices);
  if (result != VK_SUCCESS) {
    // NOLINTBEGIN(cppcoreguidelines-no-malloc,cppcoreguidelines-owning-memory,google-readability-casting,bugprone-multi-level-implicit-pointer-conversion)
    free((void*)devices);
    throw std::runtime_error("Vulkan: Failed to enumerate physical devices");
    // NOLINTEND(cppcoreguidelines-no-malloc,cppcoreguidelines-owning-memory,google-readability-casting,bugprone-multi-level-implicit-pointer-conversion)
  }

  // Collect information about each physical device
  // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
  devicesProperties = static_cast<VkPhysicalDeviceProperties*>(
      // NOLINTNEXTLINE(cppcoreguidelines-no-malloc)
      malloc(sizeof(VkPhysicalDeviceProperties) * deviceCount));

  // Print information about each physical device
  std::cout << "Found" << deviceCount << " Vulkan-compatible device(s):\n";
  for (uint32_t i = 0; i < deviceCount; ++i) {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    VkPhysicalDeviceProperties* deviceProperties = &devicesProperties[i];
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    vkGetPhysicalDeviceProperties(devices[i], deviceProperties);
  }

  // NOLINTNEXTLINE(cppcoreguidelines-owning-memory,cppcoreguidelines-no-malloc)
  prioritizedIndexes =
      // NOLINTNEXTLINE(cppcoreguidelines-no-malloc)
      static_cast<uint32_t*>(malloc(sizeof(uint32_t) * deviceCount));
  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
  sortDevicesByPriority(devicesProperties, deviceCount, &prioritizedIndexes[0]);

  for (uint32_t i = 0; i < deviceCount; ++i) {
    VkPhysicalDeviceProperties* deviceProperties =
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        &devicesProperties[prioritizedIndexes[i]];
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    std::cout << "Device " << prioritizedIndexes[i]
              << " (id=" << deviceProperties->deviceName
              << "): " << GetDeviceTypeName(deviceProperties->deviceType)
              << "\n";
  }
}

void getRecommendedResolutionForDevice() {
  // Get the primary monitor. For a specific monitor, you might need a different
  // approach.
  GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
  if (primaryMonitor == nullptr) {
    return;
  }

  // Get the current video mode of the monitor
  glfw_currentVideoMode = glfwGetVideoMode(primaryMonitor);

  // Cleanup GLFW
}

const char* GetDeviceTypeName(VkPhysicalDeviceType deviceType) {
  switch (deviceType) {
    case VK_PHYSICAL_DEVICE_TYPE_OTHER:
      return "Other";
    case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
      return "Integrated GPU";
    case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
      return "Discrete GPU";
    case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
      return "Virtual GPU";
    case VK_PHYSICAL_DEVICE_TYPE_CPU:
      return "CPU";
    default:
      return "Unknown";
  }
}

VulkanInstance::~VulkanInstance() {
  if (m_vulkan_context == nullptr) {
    return;
  }

  if (m_vulkan_context->instance != nullptr &&
      m_vulkan_context->surface != nullptr) {
    vkDestroySurfaceKHR(m_vulkan_context->instance, m_vulkan_context->surface,
                        nullptr);
  }

  if (m_vulkan_context->instance != nullptr) {
    vkDestroyInstance(m_vulkan_context->instance, nullptr);
  }

  if (m_vulkan_context->window != nullptr) {
    glfwDestroyWindow(m_vulkan_context->window);
  }
  glfwTerminate();
}

}  // namespace nextgen::engine::rendering::vulkan
