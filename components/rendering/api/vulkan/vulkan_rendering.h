#ifndef NEXTGEN_ENGINE_VULKAN_RENDERING_H
#define NEXTGEN_ENGINE_VULKAN_RENDERING_H

#include <iostream>

#include "components/configuration/config_manager.h"
#include "components/engine/nextgen_game_engine_interfaces.h"
#include "components/rendering/api/vulkan/vulkan_buffer.h"
#include "components/rendering/api/vulkan/vulkan_command_pool.h"
#include "components/rendering/api/vulkan/vulkan_context.h"
#include "components/rendering/api/vulkan/vulkan_device.hh"
#include "components/rendering/api/vulkan/vulkan_frame_buffers.h"
#include "components/rendering/api/vulkan/vulkan_instance.h"
#include "components/rendering/api/vulkan/vulkan_pipeline.h"
#include "components/rendering/api/vulkan/vulkan_render_pass.h"
#include "components/rendering/api/vulkan/vulkan_swapchain.h"
#include "components/rendering/api/vulkan/vulkan_validation_layers.h"
#include "components/rendering/rendering_api.h"
#include "vulkan_config.h"

namespace nextgen::engine::rendering::vulkan {

using configuration::ComponentConfig;
using interfaces::IConfigurable;
using nextgen::engine::rendering::api::IRenderingApi;

// NOLINTBEGIN(misc-non-private-member-variables-in-classes)
struct VulkanRenderingApi : public IRenderingApi, IConfigurable {
  ComponentConfig m_componentConfig;

  /* SUB COMPONENTS - order here is crucial. For example, m_config can be
   * initialized only when Vulkan instance is already in place for default
   * configuration to load if needed (detecting recommended graphics device and
   * resolution)*/
  VulkanContext vulkan_context_;
  VulkanInstance vulkan_instance_;
  VulkanValidationLayers vulkan_validation_layers_{};
  VulkanConfig vulkan_config_{};
  VulkanDevice m_vulkan_device;
  VulkanSwapChain m_vulkan_swap_chain;
  VulkanBuffer vulkan_buffer_{};
  VulkanCommandPool vulkan_command_pool_{};
  FrameBuffers vulkan_frame_buffers_{};
  GraphicsPipeline graphics_pipeline_{};
  VulkanRenderPass vulkan_render_pass_{};

  explicit VulkanRenderingApi() {
    std::cout << "VulkanRenderingApi object created\n";
  }

  void Initialize();

  void StartUp() override;
  void Shutdown() override;

  void Render() override;
  bool Exiting() override;

  void ApplyConfiguration(const void* config) override;

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
  VulkanRenderingApi& operator=(VulkanRenderingApi&&) noexcept = default;

 private:
  void drawFrame(VkDevice device, VkQueue graphicsQueue,
                 VkSwapchainKHR swapChain, VkSemaphore imageAvailableSemaphore,
                 VkSemaphore renderFinishedSemaphore, VkFence inFlightFence,
                 std::vector<VkCommandBuffer> commandBuffers);

  void createSyncObjects();
};
// NOLINTEND(misc-non-private-member-variables-in-classes)

}  // namespace nextgen::engine::rendering::vulkan

#endif
