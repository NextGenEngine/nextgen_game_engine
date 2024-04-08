#ifndef NEXTGEN_ENGINE_RENDERING_CONFIG_H
#define NEXTGEN_ENGINE_RENDERING_CONFIG_H

#include <yaml-cpp/yaml.h>

#include "lib/std_ext.h"

namespace nextgen::engine::rendering {

enum class RenderingAPI {
  Vulkan,
  DirectX,
  OpenGL,
};

struct RenderingEngineConfig {
  RenderingAPI api;
};

}  // namespace nextgen::engine::rendering

namespace YAML {
using nextgen::engine::rendering::RenderingAPI;
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
    rhs.api = node["api"].as<RenderingAPI>();
    // Decode other settings as needed
    return true;
  }
};

template <>
struct convert<nextgen::engine::rendering::RenderingAPI> {
  static Node encode(const nextgen::engine::rendering::RenderingAPI& rhs) {
    Node node;
    switch (rhs) {
      case nextgen::engine::rendering::RenderingAPI::Vulkan:
        node = "Vulkan";
        break;
      case nextgen::engine::rendering::RenderingAPI::DirectX:
        node = "DirectX";
        break;
      case nextgen::engine::rendering::RenderingAPI::OpenGL:
        node = "OpenGL";
        break;
    }
    return node;
  }

  static bool decode(const Node& node,
                     nextgen::engine::rendering::RenderingAPI& rhs) {
    if (!node.IsScalar()) {
      return false;
    }
    auto api = toLowerCase(node.as<std::string>());
    if (api == "vulkan") {
      rhs = nextgen::engine::rendering::RenderingAPI::Vulkan;
    } else if (api == "directx") {
      rhs = nextgen::engine::rendering::RenderingAPI::DirectX;
    } else if (api == "opengl") {
      rhs = nextgen::engine::rendering::RenderingAPI::OpenGL;
    } else {
      return false;  // Unknown value
    }
    return true;
  }
};

}  // namespace YAML

#endif
