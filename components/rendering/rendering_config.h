#ifndef NEXTGEN_ENGINE_RENDERING_CONFIG_H
#define NEXTGEN_ENGINE_RENDERING_CONFIG_H

#include <yaml-cpp/yaml.h>

#include "lib/std_ext.h"

namespace nextgen::engine::rendering {

enum class RenderingAPIEnum : std::uint8_t {
  Vulkan,
  DirectX,
  OpenGL,
};

struct RenderingEngineConfig {
  RenderingAPIEnum api;
};

}  // namespace nextgen::engine::rendering

namespace YAML {
using nextgen::engine::rendering::RenderingAPIEnum;
using nextgen::engine::rendering::RenderingEngineConfig;
using nextgen::lib::std_ext::toLowerCase;

template <>
struct convert<RenderingEngineConfig> {
  static Node encode(const RenderingEngineConfig& rhs) {
    Node node;
    node["api"] = rhs.api;
    return node;
  }

  static bool decode(const Node& node, RenderingEngineConfig& rhs) {
    // check required settings first
    // ...

    // decode
    rhs.api = node["api"].as<RenderingAPIEnum>();
    // Decode other settings as needed
    return true;
  }
};

template <>
struct convert<nextgen::engine::rendering::RenderingAPIEnum> {
  static Node encode(const nextgen::engine::rendering::RenderingAPIEnum& rhs) {
    Node node;
    switch (rhs) {
      case nextgen::engine::rendering::RenderingAPIEnum::Vulkan:
        node = "Vulkan";
        break;
      case nextgen::engine::rendering::RenderingAPIEnum::DirectX:
        node = "DirectX";
        break;
      case nextgen::engine::rendering::RenderingAPIEnum::OpenGL:
        node = "OpenGL";
        break;
    }
    return node;
  }

  static bool decode(const Node& node,
                     nextgen::engine::rendering::RenderingAPIEnum& rhs) {
    if (!node.IsScalar()) {
      return false;
    }
    auto api = toLowerCase(node.as<std::string>());
    if (api == "vulkan") {
      rhs = nextgen::engine::rendering::RenderingAPIEnum::Vulkan;
    } else if (api == "directx") {
      rhs = nextgen::engine::rendering::RenderingAPIEnum::DirectX;
    } else if (api == "opengl") {
      rhs = nextgen::engine::rendering::RenderingAPIEnum::OpenGL;
    } else {
      return false;  // Unknown value
    }
    return true;
  }
};

}  // namespace YAML

#endif
