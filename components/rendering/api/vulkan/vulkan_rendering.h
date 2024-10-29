#ifndef NEXTGEN_ENGINE_VULKAN_RENDERING_H
#define NEXTGEN_ENGINE_VULKAN_RENDERING_H

#include "components/configuration/repository/config_repo.h"
#include "components/engine/nextgen_game_engine_interfaces.h"
#include "components/rendering/api/vulkan/vulkan_buffer.h"
#include "components/rendering/api/vulkan/vulkan_command_buffers.h"
#include "components/rendering/api/vulkan/vulkan_command_pool.h"
#include "components/rendering/api/vulkan/vulkan_context.h"
#include "components/rendering/api/vulkan/vulkan_depth_resources.h"
#include "components/rendering/api/vulkan/vulkan_descriptor_pool.h"
#include "components/rendering/api/vulkan/vulkan_descriptor_set.h"
#include "components/rendering/api/vulkan/vulkan_descriptor_set_layout.h"
#include "components/rendering/api/vulkan/vulkan_device.hh"
#include "components/rendering/api/vulkan/vulkan_frame_buffers.h"
#include "components/rendering/api/vulkan/vulkan_index_buffer.h"
#include "components/rendering/api/vulkan/vulkan_instance.h"
#include "components/rendering/api/vulkan/vulkan_model_loader.h"
#include "components/rendering/api/vulkan/vulkan_pipeline.h"
#include "components/rendering/api/vulkan/vulkan_render_pass.h"
#include "components/rendering/api/vulkan/vulkan_swapchain.h"
#include "components/rendering/api/vulkan/vulkan_sync_object.h"
#include "components/rendering/api/vulkan/vulkan_texture_image.h"
#include "components/rendering/api/vulkan/vulkan_uniform_buffer.h"
#include "components/rendering/api/vulkan/vulkan_validation_layers.h"
#include "components/rendering/api/vulkan/vulkan_vertex_buffer.h"
#include "components/rendering/rendering_api.h"
#include "vulkan_config.h"

namespace nextgen::engine::rendering::vulkan {

using configuration::ConfigRepositoryNode;
using interfaces::IConfigurable;
using nextgen::engine::rendering::api::IRenderingApi;

// NOLINTBEGIN(misc-non-private-member-variables-in-classes)
struct VulkanRenderingApi : public IRenderingApi, IConfigurable<VulkanConfig> {
  /* SUB COMPONENTS - order here is crucial. For example, m_config can be
   * initialized only when Vulkan instance is already in place for default
   * configuration to load if needed (detecting recommended graphics device and
   * resolution)*/
  VulkanContext vulkan_context_;
  VulkanInstance vulkan_instance_;
  VulkanValidationLayers vulkan_validation_layers_;
  VulkanConfig vulkan_config_{};
  VulkanDevice vulkan_device_;
  VulkanSwapChain vulkan_swap_chain_;
  VulkanDescriptorSetLayout vulkan_descriptor_set_layout_;
  VulkanBuffer vulkan_buffer_;
  VulkanCommandPool vulkan_command_pool_;
  VulkanFrameBuffers vulkan_frame_buffers_;
  VulkanTextureImage vulkan_texture_image_;
  VulkanGraphicsPipeline graphics_pipeline_;
  VulkanRenderPass vulkan_render_pass_;
  VulkanDepthResources vulkan_depth_resources_;
  VulkanCommandBuffers vulkan_command_buffers_;
  VulkanModelLoader vulkan_model_loader_;
  VulkanVertexBuffer vulkan_vertex_buffer_;
  VulkanIndexBuffer vulkan_index_buffer_;
  VulkanUniformBuffer vulkan_uniform_buffer_;
  VulkanDescriptorPool vulkan_descriptor_pool_;
  VulkanDescriptorSet vulkan_descriptor_set_;
  VulkanSyncObject vulkan_sync_object_;

  explicit VulkanRenderingApi();

  void Initialize() override;
  void Shutdown() override;

  void MainLoop() override;

  void Render() override;
  bool Exiting() override;

  void ApplyConfiguration(const VulkanConfig& config) override;

  VulkanRenderingApi& set_config(const VulkanConfig& vulkan_config) {
    vulkan_config_ = vulkan_config;
    return *this;
  }
  VulkanRenderingApi& set_context(const VulkanContext& vulkan_context) {
    vulkan_context_ = vulkan_context;
    return *this;
  }

  // Getter for VulkanContext
  VulkanContext& get_vulkan_context_ref() { return vulkan_context_; }
  const VulkanContext& get_vulkan_context_ref() const {
    return vulkan_context_;
  }
  // Getter for VulkanConfig
  VulkanConfig& get_vulkan_config_ref() { return vulkan_config_; }
  const VulkanConfig& get_vulkan_config_ref() const { return vulkan_config_; }

  // delete
  ~VulkanRenderingApi() override;
  // copy
  VulkanRenderingApi(const VulkanRenderingApi&) = delete;
  VulkanRenderingApi& operator=(const VulkanRenderingApi&) = delete;
  // move
  VulkanRenderingApi(VulkanRenderingApi&&) noexcept = default;
  VulkanRenderingApi& operator=(VulkanRenderingApi&&) noexcept = delete;

 private:
  void drawFrame();
  void RecreateSwapChain();
  void CleanupSwapChain() const;
  void updateUniformBuffer(uint32_t currentImage);
  void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
};
// NOLINTEND(misc-non-private-member-variables-in-classes)

}  // namespace nextgen::engine::rendering::vulkan

#endif
