#include "components/rendering/api/vulkan/vulkan_model_loader.h"

#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#include "components/rendering/api/vulkan/vulkan_context.h"
#include "components/rendering/api/vulkan/vulkan_types.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

namespace nextgen::engine::rendering::vulkan {

const std::string MODEL_PATH = "data/models/viking_room.obj";

VulkanModelLoader::VulkanModelLoader(VulkanContext& vulkan_context)
    : vulkan_context_(vulkan_context) {
  std::cout << "VulkanModelLoader object instantiated\n";
}

VulkanModelLoader::~VulkanModelLoader() {
  std::cout << "VulkanModelLoader instance destroyed\n";
}

void VulkanModelLoader::Initialize() { LoadModel(); }

void VulkanModelLoader::Shutdown() const noexcept {
  vulkan_context_.vertices.clear();
  vulkan_context_.indices.clear();
  std::cout << "VulkanModelLoader: shutdown complete\n";
}

void VulkanModelLoader::LoadModel() const {
  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  std::string warn;
  std::string err;

  if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err,
                        MODEL_PATH.c_str())) {
    throw std::runtime_error(warn + err);
  }

  std::unordered_map<Vertex, uint32_t> uniqueVertices{};

  for (const auto& shape : shapes) {
    for (const auto& index : shape.mesh.indices) {
      Vertex vertex{};

      vertex.pos = {attrib.vertices[(3 * index.vertex_index) + 0],
                    attrib.vertices[(3 * index.vertex_index) + 1],
                    attrib.vertices[(3 * index.vertex_index) + 2]};

      vertex.texCoord = {
          attrib.texcoords[(2 * index.texcoord_index) + 0],
          1.0F - attrib.texcoords[(2 * index.texcoord_index) + 1]};

      vertex.color = {1.0F, 1.0F, 1.0F};

      if (!uniqueVertices.contains(vertex)) {
        uniqueVertices[vertex] =
            static_cast<uint32_t>(vulkan_context_.vertices.size());
        vulkan_context_.vertices.push_back(vertex);
      }

      vulkan_context_.indices.push_back(uniqueVertices[vertex]);
    }
  }
}

}  // namespace nextgen::engine::rendering::vulkan
