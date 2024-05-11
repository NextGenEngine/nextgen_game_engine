#include "vulkan_device.hh"

#include <vulkan/vulkan_core.h>

#include <cstdint>
#include <cstring>
#include <stdexcept>

#include "components/rendering/api/vulkan/vulkan_config.h"
#include "components/rendering/api/vulkan/vulkan_context.h"

namespace nextgen::engine::rendering::vulkan {

using nextgen::engine::rendering::vulkan::VulkanContext;

void VulkanDevice::Initialize(VulkanContext& vulkan_context,
                              VulkanConfig& vulkan_config) {
  m_vulkan_context = &vulkan_context;
  m_vulkan_config = &vulkan_config;
}

void VulkanDevice::CreateDevice() {
  auto& instance = m_vulkan_context->instance;
  auto& physicalDevice = m_vulkan_context->physical_device;
  auto& device = m_vulkan_context->device;
  auto& graphicsQueue = m_vulkan_context->graphics_queue;

  // Create a logical device from the selected physical device
  uint32_t deviceCount = 0;
  vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
  if (deviceCount == 0) {
    throw std::runtime_error(
        "Failed to find GPUs with Vulkan support: "
        "vkEnumeratePhysicalDevices()");
  }

  // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,modernize-avoid-c-arrays,-Wvla-cxx-extension,clang-diagnostic-vla-cxx-extension)
  VkPhysicalDevice devices[deviceCount];
  vkEnumeratePhysicalDevices(instance, &deviceCount, devices);
  physicalDevice = devices[0];  // Simplification: Just select the first device

  // Check for swap chain support
  uint32_t extensionCount = 0;
  vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount,
                                       nullptr);
  // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,modernize-avoid-c-arrays,-Wvla-cxx-extension,clang-diagnostic-vla-cxx-extension)
  VkExtensionProperties availableExtensions[extensionCount];
  vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount,
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
    throw std::runtime_error(
        "Vulkan: Swapchain not supported on selected device");
  }

  const float queuePriority = 1.0F;
  const VkDeviceQueueCreateInfo queueCreateInfo = {
      .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
      .queueFamilyIndex = 0,  // This is simplified; you should search for the
                              // proper queue family
      .queueCount = 1,
      .pQueuePriorities = &queuePriority,
  };

  // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,modernize-avoid-c-arrays,-Wvla-cxx-extension,clang-diagnostic-vla-cxx-extension)
  const char* deviceExtensions[] = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
  const VkDeviceCreateInfo createInfo = {
      .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
      .queueCreateInfoCount = 1,
      .pQueueCreateInfos = &queueCreateInfo,
      .enabledExtensionCount = 1,
      .ppEnabledExtensionNames = deviceExtensions,
  };

  if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) !=
      VK_SUCCESS) {
    throw std::runtime_error("Vulkan: Failed to create logical device");
  }

  vkGetDeviceQueue(device, 0, 0, &graphicsQueue);  // Simplification
}

VulkanDevice::~VulkanDevice() {
  if (m_vulkan_context == nullptr || m_vulkan_context->device == nullptr) {
    return;
  }
  vkDestroyDevice(m_vulkan_context->device, nullptr);
}

}  // namespace nextgen::engine::rendering::vulkan
