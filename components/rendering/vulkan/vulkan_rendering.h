#ifndef NEXTGEN_ENGINE_VULKAN_RENDERING_H
#define NEXTGEN_ENGINE_VULKAN_RENDERING_H

#include <vulkan/vulkan_core.h>
#include <yaml-cpp/exceptions.h>

#include <iostream>
#include <utility>

#include "components/configuration/config_manager.h"
#include "components/rendering/vulkan/vulkan_operations.h"
#include "vulkan_config.h"

VulkanConfig getDefaultConfig();

template <typename ConfigManagerType>
class VulkanApi {
 private:
  ComponentConfig config;
  ConfigManagerType configManager;
  VulkanConfig vulkanConfig;

 public:
  explicit VulkanApi(ComponentConfig config, ConfigManagerType configManager)
      : config(config.getSubConfig("vulkan")),
        configManager(std::move(configManager)),
        vulkanConfig([this]() -> VulkanConfig {
          vulkan_init();
          try {
            // Attempt to use the provided configuration
            return this->config().template as<VulkanConfig>();
          } catch (const YAML::Exception &e) {
            // Log the error and use default values on failure
            std::cerr << "Failed to decode VulkanConfig: " << e.what() << "\n";
            auto defaultVulkanConfig = getDefaultConfig();
            this->config() = defaultVulkanConfig;
            this->configManager.Save();
            return defaultVulkanConfig;
          }
        }()) {}

  void render();

  // Delete copy constructor and copy assignment operator
  VulkanApi(const VulkanApi &) = delete;
  VulkanApi &operator=(const VulkanApi &) = delete;
  ~VulkanApi() = default;             // Default destructor
  VulkanApi(VulkanApi &&) = default;  // Default move constructor
  VulkanApi &operator=(VulkanApi &&) =
      default;  // Default move assignment operator
};

#endif
