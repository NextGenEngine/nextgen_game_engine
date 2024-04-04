#ifndef NEXTGEN_ENGINE_VULKAN_CONFIG_H
#define NEXTGEN_ENGINE_VULKAN_CONFIG_H
#include <vulkan/vulkan.h>
#include <yaml-cpp/yaml.h>

using VulkanConfig = struct VulkanConfig {
  uint32_t deviceID;  // ID for the physical device (GPU) to be used
  uint32_t width;     // Width of the window or surface
  uint32_t height;    // Height of the window or surface
  float refreshRate;  // Refresh rate in Hz
};

namespace YAML {
template <>
struct convert<VulkanConfig> {
  static Node encode(const VulkanConfig& rhs) {
    Node node;
    node["deviceID"] = rhs.deviceID;
    node["width"] = rhs.width;
    node["height"] = rhs.height;
    node["refreshRate"] = rhs.refreshRate;
    return node;
  }

  static bool decode(const Node& node, VulkanConfig& rhs) {
    // check required settings first
    // ...

    // decode
    rhs.deviceID = node["deviceID"].as<uint32_t>();
    rhs.width = node["width"].as<uint32_t>();
    rhs.height = node["height"].as<uint32_t>();
    rhs.refreshRate = node["refreshRate"].as<float>();
    // Decode other settings as needed
    return true;
  }
};
}  // namespace YAML

#endif
