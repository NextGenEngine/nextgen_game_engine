#ifndef NEXTGEN_ENGINE_VULKAN_CONFIG_H
#define NEXTGEN_ENGINE_VULKAN_CONFIG_H
#include <vulkan/vulkan.h>
#include <yaml-cpp/yaml.h>

namespace nextgen::engine::rendering::vulkan {

struct VulkanConfig {
  uint32_t device_id;  // ID for the physical device (GPU) to be used
  uint32_t width;      // Width of the window or surface
  uint32_t height;     // Height of the window or surface
  float refresh_rate;  // Refresh rate in Hz
};

}  // namespace nextgen::engine::rendering::vulkan

namespace YAML {
using nextgen::engine::rendering::vulkan::VulkanConfig;
template <>
struct convert<VulkanConfig> {
  static Node encode(const VulkanConfig& rhs) {
    Node node;
    node["device_id"] = rhs.device_id;
    node["width"] = rhs.width;
    node["height"] = rhs.height;
    node["refresh_rate"] = rhs.refresh_rate;
    return node;
  }

  static bool decode(const Node& node, VulkanConfig& rhs) {
    // check required settings first
    // ...

    // decode
    rhs.device_id = node["device_id"].as<uint32_t>();
    rhs.width = node["width"].as<uint32_t>();
    rhs.height = node["height"].as<uint32_t>();
    rhs.refresh_rate = node["refresh_rate"].as<float>();
    // Decode other settings as needed
    return true;
  }
};
}  // namespace YAML

#endif
