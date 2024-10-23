#include "vulkan_device.hh"

#include <vulkan/vulkan_core.h>

#include <cstdint>
#include <cstring>
#include <iostream>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

#include "components/rendering/api/vulkan/vulkan_config.h"
#include "components/rendering/api/vulkan/vulkan_context.h"
#include "components/rendering/api/vulkan/vulkan_swapchain_types.h"

namespace nextgen::engine::rendering::vulkan {

using nextgen::engine::rendering::vulkan::VulkanContext;

void VulkanDevice::Initialize(VulkanContext& vulkan_context,
                              VulkanConfig& vulkan_config) {
  m_vulkan_context = &vulkan_context;
  m_vulkan_config = &vulkan_config;

  pickPhysicalDevice();
  createLogicalDevice();
}

void VulkanDevice::Shutdown() const noexcept {
  // TODO(artem): Check if destroying debug messenger must be here.
  //  Most probably it must be in validation layers class
  if (m_vulkan_context != nullptr &&
      m_vulkan_context->enable_validation_layers) {
    DestroyDebugUtilsMessengerEXT(nullptr);
    std::cout << "VulkanDevice: DebugUtilsMessengerEXT destroyed\n";
  } else {
    std::cout
        << "VulkanDevice: Validation layers are disabled. No need to destroy "
           "DebugUtilsMessengerEXT\n";
  }
  if (m_vulkan_context != nullptr &&
      m_vulkan_context->device != VK_NULL_HANDLE) {
    vkDestroyDevice(m_vulkan_context->device, nullptr);
    m_vulkan_context->device = VK_NULL_HANDLE;
    std::cout << "VulkanDevice: vkDevice destroyed\n";
  } else {
    std::cout << "VulkanDevice: vkDevice does not exist. Cannot destroy it\n";
  }
  std::cout << "VulkanDevice: shutdown complete\n";
}

void VulkanDevice::pickPhysicalDevice() {
  uint32_t deviceCount = 0;
  vkEnumeratePhysicalDevices(m_vulkan_context->instance, &deviceCount, nullptr);

  if (deviceCount == 0) {
    throw std::runtime_error("failed to find GPUs with Vulkan support!");
  }

  std::vector<VkPhysicalDevice> devices(deviceCount);
  vkEnumeratePhysicalDevices(m_vulkan_context->instance, &deviceCount,
                             devices.data());

  for (const auto& device : devices) {
    if (isDeviceSuitable(device)) {
      m_vulkan_context->physical_device = device;
      break;
    }
  }

  if (m_vulkan_context->physical_device == VK_NULL_HANDLE) {
    throw std::runtime_error("failed to find a suitable GPU!");
  }
}

bool VulkanDevice::isDeviceSuitable(VkPhysicalDevice device) {
  QueueFamilyIndices indices = findQueueFamilies(device);

  auto extensionsSupported = checkDeviceExtensionSupport(device);

  bool swapChainAdequate = false;
  if (extensionsSupported) {
    SwapChainSupportDetails const swapChainSupport =
        querySwapChainSupport(device);
    swapChainAdequate = !swapChainSupport.formats.empty() &&
                        !swapChainSupport.presentModes.empty();
  }

  VkPhysicalDeviceFeatures supportedFeatures;
  vkGetPhysicalDeviceFeatures(device, &supportedFeatures);

  return indices.isComplete() && extensionsSupported && swapChainAdequate &&
         (supportedFeatures.samplerAnisotropy != 0U);
}

QueueFamilyIndices VulkanDevice::findQueueFamilies(
    VkPhysicalDevice device) const {
  QueueFamilyIndices indices;

  uint32_t queueFamilyCount = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

  std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
  vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount,
                                           queueFamilies.data());

  int index = 0;
  for (const auto& queueFamily : queueFamilies) {
    if ((queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0U) {
      indices.graphicsFamily = index;
    }

    VkBool32 presentSupport = 0U;  // false
    vkGetPhysicalDeviceSurfaceSupportKHR(
        device, index, m_vulkan_context->surface, &presentSupport);

    if (presentSupport != 0U) {
      indices.presentFamily = index;
    }

    if (indices.isComplete()) {
      break;
    }

    index++;
  }

  return indices;
}

bool VulkanDevice::checkDeviceExtensionSupport(VkPhysicalDevice device) {
  uint32_t extensionCount = 0;
  vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount,
                                       nullptr);

  std::vector<VkExtensionProperties> availableExtensions(extensionCount);
  vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount,
                                       availableExtensions.data());

  std::set<std::string> requiredExtensions(deviceExtensions.begin(),
                                           deviceExtensions.end());

  for (const auto& extension : availableExtensions) {
    requiredExtensions.erase(extension.extensionName);
  }

  return requiredExtensions.empty();
}

SwapChainSupportDetails VulkanDevice::querySwapChainSupport(
    VkPhysicalDevice device) const {
  SwapChainSupportDetails details;

  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, m_vulkan_context->surface,
                                            &details.capabilities);

  uint32_t formatCount = 0;
  vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_vulkan_context->surface,
                                       &formatCount, nullptr);

  if (formatCount != 0) {
    details.formats.resize(formatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_vulkan_context->surface,
                                         &formatCount, details.formats.data());
  }

  uint32_t presentModeCount = 0;
  vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_vulkan_context->surface,
                                            &presentModeCount, nullptr);

  if (presentModeCount != 0) {
    details.presentModes.resize(presentModeCount);
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_vulkan_context->surface,
                                              &presentModeCount,
                                              details.presentModes.data());
  }

  return details;
}

void VulkanDevice::createLogicalDevice() {
  QueueFamilyIndices indices =
      findQueueFamilies(m_vulkan_context->physical_device);

  if (!indices.graphicsFamily.has_value() ||
      !indices.presentFamily.has_value()) {
    throw std::runtime_error("cannot find required queue families!");
  }

  std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
  std::set<uint32_t> const uniqueQueueFamilies = {
      indices.graphicsFamily.value(), indices.presentFamily.value()};

  float const queuePriority = 1.0F;
  for (uint32_t const queueFamily : uniqueQueueFamilies) {
    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = queueFamily;
    queueCreateInfo.queueCount = 1;
    queueCreateInfo.pQueuePriorities = &queuePriority;
    queueCreateInfos.push_back(queueCreateInfo);
  }

  VkPhysicalDeviceFeatures deviceFeatures{};
  deviceFeatures.samplerAnisotropy = VK_TRUE;

  VkDeviceCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

  createInfo.queueCreateInfoCount =
      static_cast<uint32_t>(queueCreateInfos.size());
  createInfo.pQueueCreateInfos = queueCreateInfos.data();

  createInfo.pEnabledFeatures = &deviceFeatures;

  createInfo.enabledExtensionCount =
      static_cast<uint32_t>(deviceExtensions.size());
  createInfo.ppEnabledExtensionNames = deviceExtensions.data();

  if (m_vulkan_context->enable_validation_layers) {
    createInfo.enabledLayerCount =
        static_cast<uint32_t>(m_vulkan_context->validation_layers.size());
    createInfo.ppEnabledLayerNames = m_vulkan_context->validation_layers.data();
  } else {
    createInfo.enabledLayerCount = 0;
  }

  if (vkCreateDevice(m_vulkan_context->physical_device, &createInfo, nullptr,
                     &m_vulkan_context->device) != VK_SUCCESS) {
    throw std::runtime_error("failed to create logical device!");
  }

  vkGetDeviceQueue(m_vulkan_context->device, indices.graphicsFamily.value(), 0,
                   &m_vulkan_context->graphics_queue);
  vkGetDeviceQueue(m_vulkan_context->device, indices.presentFamily.value(), 0,
                   &m_vulkan_context->present_queue);
}

void VulkanDevice::DestroyDebugUtilsMessengerEXT(
    const VkAllocationCallbacks* pAllocator) const {
  // NOLINTNEXTLINE(google-readability-casting,cppcoreguidelines-pro-type-cstyle-cast)
  auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
      m_vulkan_context->instance, "vkDestroyDebugUtilsMessengerEXT");
  if (func != nullptr) {
    func(m_vulkan_context->instance, m_vulkan_context->debug_messenger,
         pAllocator);
  }
}

VkFormat VulkanDevice::findSupportedFormat(
    const std::vector<VkFormat>& candidates, VkImageTiling tiling,
    VkFormatFeatureFlags features) const {
  for (VkFormat const format : candidates) {
    VkFormatProperties props;
    vkGetPhysicalDeviceFormatProperties(m_vulkan_context->physical_device,
                                        format, &props);

    if (tiling == VK_IMAGE_TILING_LINEAR &&
        (props.linearTilingFeatures & features) == features) {
      return format;
    }

    if (tiling == VK_IMAGE_TILING_OPTIMAL &&
        (props.optimalTilingFeatures & features) == features) {
      return format;
    }
  }

  throw std::runtime_error("failed to find supported format!");
}

VkFormat VulkanDevice::findDepthFormat() const {
  return findSupportedFormat(
      {VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT,
       VK_FORMAT_D24_UNORM_S8_UINT},
      VK_IMAGE_TILING_OPTIMAL, VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
}

uint32_t VulkanDevice::FindMemoryType(uint32_t typeFilter,
                                      VkMemoryPropertyFlags properties) const {
  VkPhysicalDeviceMemoryProperties memProperties;
  vkGetPhysicalDeviceMemoryProperties(m_vulkan_context->physical_device,
                                      &memProperties);

  for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
    if (((typeFilter & (1 << i)) != 0U) &&
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
        (memProperties.memoryTypes[i].propertyFlags & properties) ==
            properties) {
      return i;
    }
  }

  throw std::runtime_error("failed to find suitable memory type!");
}

VkImageView VulkanDevice::CreateImageView(
    VkImage image, VkFormat format, VkImageAspectFlags aspectFlags) const {
  VkImageViewCreateInfo viewInfo{};
  viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
  viewInfo.image = image;
  viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
  viewInfo.format = format;
  viewInfo.subresourceRange.aspectMask = aspectFlags;
  viewInfo.subresourceRange.baseMipLevel = 0;
  viewInfo.subresourceRange.levelCount = 1;
  viewInfo.subresourceRange.baseArrayLayer = 0;
  viewInfo.subresourceRange.layerCount = 1;

  VkImageView imageView = nullptr;
  if (vkCreateImageView(m_vulkan_context->device, &viewInfo, nullptr,
                        &imageView) != VK_SUCCESS) {
    throw std::runtime_error("failed to create image view!");
  }

  return imageView;
}

VulkanDevice::~VulkanDevice() {
  std::cout << "VulkanDevice instance destroyed\n";
}

}  // namespace nextgen::engine::rendering::vulkan
