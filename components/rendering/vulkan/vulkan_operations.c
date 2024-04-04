#include "vulkan_operations.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vulkan/vulkan_core.h>

#include "vulkan_device_priority.h"

VkInstance instance;
VkDevice device;
VkPhysicalDevice physicalDevice;
VkQueue graphicsQueue;
VkSurfaceKHR surface;
VkSwapchainKHR swapchain;
GLFWwindow *window;

// Calculated values
VkPhysicalDevice *devices = NULL;
VkPhysicalDeviceProperties *devicesProperties = NULL;
uint32_t *prioritizedIndexes = NULL;
uint32_t deviceCount = 0;
const GLFWvidmode *glfw_currentVideoMode = NULL;

VkResult vulkan_init() {
  // Initialize the Vulkan library
  // Initialize GLFW
  if (!glfwInit()) {
    printf("Failed to initialize GLFW.\n");
    return VK_ERROR_INITIALIZATION_FAILED;
  }

  if (!glfwVulkanSupported()) {
    printf("Vulkan not supported on the system.\n");
    return VK_ERROR_INITIALIZATION_FAILED;
  }

  // Specify that we won't be creating an OpenGL context
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  // Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(800, 600, "Hello Vulkan", NULL, NULL);
  if (!window) {
    glfwTerminate();
    printf("Failed to create GLFW window.\n");
    return VK_ERROR_INITIALIZATION_FAILED;
  }

  // Initialize the Vulkan library
  VkApplicationInfo appInfo = {0};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName = "Hello Vulkan";
  appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.pEngineName = "No Engine";
  appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.apiVersion = VK_API_VERSION_1_0;

  uint32_t glfwExtensionCount = 0;
  const char **glfwExtensions = NULL;
  glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

  VkInstanceCreateInfo createInfo = {0};
  createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo = &appInfo;
  createInfo.enabledExtensionCount = glfwExtensionCount;
  createInfo.ppEnabledExtensionNames = glfwExtensions;

  if (vkCreateInstance(&createInfo, NULL, &instance) != VK_SUCCESS) {
    printf("Failed to create Vulkan instance.\n");
    return VK_ERROR_INITIALIZATION_FAILED;
  }

  VkResult result = glfwCreateWindowSurface(instance, window, NULL, &surface);
  if (result != VK_SUCCESS) {
    printf("Failed to create window surface.\n");
    return result;
  }

  printf("Vulkan initialized with GLFW window and surface.\n");
  return VK_SUCCESS;
}

VkResult vulkan_create_device() {
  // Create a logical device from the selected physical device
  uint32_t deviceCount = 0;
  vkEnumeratePhysicalDevices(instance, &deviceCount, NULL);
  if (deviceCount == 0) {
    printf("Failed to find GPUs with Vulkan support.\n");
    return VK_ERROR_INITIALIZATION_FAILED;
  }

  VkPhysicalDevice devices[deviceCount];
  vkEnumeratePhysicalDevices(instance, &deviceCount, devices);
  physicalDevice = devices[0];  // Simplification: Just select the first device

  // Check for swap chain support
  uint32_t extensionCount = 0;
  vkEnumerateDeviceExtensionProperties(physicalDevice, NULL, &extensionCount,
                                       NULL);
  VkExtensionProperties availableExtensions[extensionCount];
  vkEnumerateDeviceExtensionProperties(physicalDevice, NULL, &extensionCount,
                                       availableExtensions);

  bool swapChainSupported = false;
  for (uint32_t i = 0; i < extensionCount; i++) {
    if (strcmp(VK_KHR_SWAPCHAIN_EXTENSION_NAME,
               availableExtensions[i].extensionName) == 0) {
      swapChainSupported = true;
      break;
    }
  }

  if (!swapChainSupported) {
    printf("Swapchain not supported on selected device.\n");
    return VK_ERROR_EXTENSION_NOT_PRESENT;
  }

  float queuePriority = 1.0F;
  VkDeviceQueueCreateInfo queueCreateInfo = {0};
  queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  queueCreateInfo.queueFamilyIndex =
      0;  // This is simplified; you should search for the proper queue family
  queueCreateInfo.queueCount = 1;
  queueCreateInfo.pQueuePriorities = &queuePriority;

  const char *deviceExtensions[] = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
  VkDeviceCreateInfo createInfo = {0};
  createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  createInfo.queueCreateInfoCount = 1;
  createInfo.pQueueCreateInfos = &queueCreateInfo;
  createInfo.enabledExtensionCount = 1;
  createInfo.ppEnabledExtensionNames = deviceExtensions;

  if (vkCreateDevice(physicalDevice, &createInfo, NULL, &device) !=
      VK_SUCCESS) {
    printf("Failed to create logical device.\n");
    return VK_ERROR_INITIALIZATION_FAILED;
  }

  vkGetDeviceQueue(device, 0, 0, &graphicsQueue);  // Simplification

  printf("Logical device created with VK_KHR_swapchain extension.\n");
  return VK_SUCCESS;
}

VkResult vulkan_create_swapchain() {
  // Create a swap chain for image presentation
  // This pseudo-code assumes surface has already been created
  VkSwapchainCreateInfoKHR createInfo = {0};
  createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  createInfo.surface = surface;
  createInfo.minImageCount = 2;                       // Double buffering
  createInfo.imageFormat = VK_FORMAT_B8G8R8A8_UNORM;  // Simplification
  createInfo.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
  createInfo.imageExtent.width = 800;  // Simplification: Fixed size
  createInfo.imageExtent.height = 600;
  createInfo.imageArrayLayers = 1;
  createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
  createInfo.presentMode = VK_PRESENT_MODE_FIFO_KHR;  // V-Sync enabled
  createInfo.clipped = VK_TRUE;
  createInfo.oldSwapchain = VK_NULL_HANDLE;

  if (vkCreateSwapchainKHR(device, &createInfo, NULL, &swapchain) !=
      VK_SUCCESS) {
    printf("Failed to create swap chain.\n");
    return VK_ERROR_INITIALIZATION_FAILED;
  }

  printf("Swap chain created.\n");
  return VK_SUCCESS;
}

typedef struct {
  float position[3];  // x, y, z coordinates
  float color[3];     // r, g, b colors
} VkVertex;

// Define vertices for a triangle and a square
const VkVertex triangleVertices[] = {
    {{0.5F, -0.5F, 0.0F}, {1.0F, 0.0F, 0.0F}},  // Vertex 1
    {{-0.5F, 0.5F, 0.0F}, {0.0F, 1.0F, 0.0F}},  // Vertex 2
    {{0.5F, 0.5F, 0.0F}, {0.0F, 0.0F, 1.0F}},   // Vertex 2
};

const VkVertex squareVertices[] = {
    {{-0.5F, -0.5F, 0.0F}, {1.0F, 0.0F, 0.0F}},  // Bottom leFt
    {{0.5F, -0.5F, 0.0F}, {0.0F, 1.0F, 0.0F}},   // Bottom right
    {{0.5F, 0.5F, 0.0F}, {0.0F, 0.0F, 1.0F}},    // Top right
    {{-0.5F, -0.5F, 0.0F},
     {1.0F, 1.0F, 0.0F}},  // Bottom leFt (repeated For triangle strip)
    {{0.5F, 0.5F, 0.0F},
     {0.0F, 1.0F, 1.0F}},  // Top right (repeated For triangle strip)
    {{-0.5F, 0.5F, 0.0F}, {1.0F, 0.0F, 1.0F}}  // Top leFt
};

VkShaderModule createShaderModule(VkDevice device, const char *filePath) {
  // Read the SPIR-V binary from file
  FILE *file = fopen(filePath, "rb");
  if (file == NULL) {
    return NULL;
  }
  fseek(file, 0, SEEK_END);
  long length = ftell(file);
  fseek(file, 0, SEEK_SET);

  uint32_t *buffer = (uint32_t *)malloc(length);
  fread(buffer, 1, length, file);
  fclose(file);

  // Create the shader module
  VkShaderModuleCreateInfo createInfo = {0};
  createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  createInfo.codeSize = length;
  createInfo.pCode = buffer;

  VkShaderModule shaderModule = NULL;
  if (vkCreateShaderModule(device, &createInfo, NULL, &shaderModule) !=
      VK_SUCCESS) {
    free(buffer);
    return VK_NULL_HANDLE;  // Error handling omitted for brevity
  }

  free(buffer);
  return shaderModule;
}

VkResult vulkan_render() {
  // Handle the rendering operations, drawing a frame
  // This is a simplified version and does not include actual rendering code
  printf("Frame rendered.\n");

  // Main loop
  while (!glfwWindowShouldClose(window)) {
    // Efficiently wait for events
    glfwWaitEvents();

    // Render a frame when there are events (e.g., window resize, input)
    // if (vulkan_render() != VK_SUCCESS) {
    //     // Handle render error
    //     break; // or continue based on your error handling strategy
    // }
  }

  return VK_SUCCESS;
}

void vulkan_cleanup() {
  // Clean up and release all Vulkan resources and the GLFW window
  vkDestroySwapchainKHR(device, swapchain, NULL);
  vkDestroyDevice(device, NULL);
  vkDestroySurfaceKHR(instance, surface, NULL);
  vkDestroyInstance(instance, NULL);
  glfwDestroyWindow(window);
  glfwTerminate();

  // free memory
  free(devicesProperties);
  free((void *)devices);
  free(prioritizedIndexes);

  printf("Vulkan and GLFW cleaned up.\n");
}

const char *getDeviceTypeName(VkPhysicalDeviceType deviceType) {
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

VkResult enumerateAvailableDevices() {
  VkResult result = 0;

  // Create Vulkan instance
  VkApplicationInfo appInfo = {VK_STRUCTURE_TYPE_APPLICATION_INFO};
  appInfo.pApplicationName = "Vulkan Device Listing";
  appInfo.apiVersion = VK_API_VERSION_1_0;

  VkInstanceCreateInfo createInfo = {VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO};
  createInfo.pApplicationInfo = &appInfo;

  result = vkCreateInstance(&createInfo, NULL, &instance);
  if (result != VK_SUCCESS) {
    printf("Failed to create Vulkan instance\n");
    return EXIT_FAILURE;
  }

  // Enumerate physical devices
  result = vkEnumeratePhysicalDevices(instance, &deviceCount, NULL);
  if (result != VK_SUCCESS) {
    printf("Failed to enumerate physical devices\n");
    return EXIT_FAILURE;
  }

  if (deviceCount == 0) {
    printf("No Vulkan-compatible devices found\n");
    return EXIT_SUCCESS;
  }

  // Allocate memory for physical devices
  devices = (VkPhysicalDevice *)malloc(sizeof(VkPhysicalDevice) * deviceCount);
  if (!devices) {
    printf("Failed to allocate memory for devices\n");
    return EXIT_FAILURE;
  }

  // Retrieve physical devices
  result = vkEnumeratePhysicalDevices(instance, &deviceCount, devices);
  if (result != VK_SUCCESS) {
    printf("Failed to enumerate physical devices\n");
    free((void *)devices);
    return EXIT_FAILURE;
  }

  // Collect information about each physical device
  devicesProperties = (VkPhysicalDeviceProperties *)malloc(
      sizeof(VkPhysicalDeviceProperties) * deviceCount);

  // Print information about each physical device
  printf("Found %d Vulkan-compatible device(s):\n", deviceCount);
  for (uint32_t i = 0; i < deviceCount; ++i) {
    VkPhysicalDeviceProperties *deviceProperties = &devicesProperties[i];
    vkGetPhysicalDeviceProperties(devices[i], deviceProperties);
  }

  prioritizedIndexes = (uint32_t *)malloc(sizeof(uint32_t) * deviceCount);
  sortDevicesByPriority(devicesProperties, deviceCount, &prioritizedIndexes[0]);

  for (uint32_t i = 0; i < deviceCount; ++i) {
    VkPhysicalDeviceProperties *deviceProperties =
        &devicesProperties[prioritizedIndexes[i]];
    printf("Device %d (id=%d): %s, %s\n", prioritizedIndexes[i],
           deviceProperties->deviceID, deviceProperties->deviceName,
           getDeviceTypeName(deviceProperties->deviceType));
  }

  return EXIT_SUCCESS;
}

void getRecommendedResolutionForDevice() {
  // Get the primary monitor. For a specific monitor, you might need a different
  // approach.
  GLFWmonitor *primaryMonitor = glfwGetPrimaryMonitor();
  if (!primaryMonitor) {
    return;
  }

  // Get the current video mode of the monitor
  glfw_currentVideoMode = glfwGetVideoMode(primaryMonitor);

  // Cleanup GLFW
}
