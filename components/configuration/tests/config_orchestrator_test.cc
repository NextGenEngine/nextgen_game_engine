// **Explanation of Tests:**

// 1. **`ConfigureCallsApplyConfigurationOnManagers_WithValidConfigs`:**
//    - **Scenario:** Both `RenderingEngine` and `VulkanRenderingApi` receive
//    valid configurations.
//    - **Expectations:**
//      - `ValidateConfig` returns the provided configuration.
//      - `GetDefaultConfig` is not called.
//      - `ApplyConfiguration` is called with the valid configurations.

// 2. **`ConfigureUsesDefaultConfigWhenValidConfigIsInvalid`:**
//    - **Scenario:** Both `RenderingEngine` and `VulkanRenderingApi` receive
//    invalid configurations.
//    - **Expectations:**
//      - `ValidateConfig` returns `std::nullopt`.
//      - `GetDefaultConfig` is called to retrieve default configurations.
//      - `ApplyConfiguration` is called with the default configurations.

// 3. **`ConfigureHandlesMixedValidAndInvalidConfigs`:**
//    - **Scenario:** `RenderingEngine` receives a valid configuration, while
//    `VulkanRenderingApi` receives an invalid configuration.
//    - **Expectations:**
//      - `RenderingEngine` applies the provided valid configuration.
//      - `VulkanRenderingApi` falls back to and applies the default
//      configuration.

// config_orchestrator_test.cc

#include "components/configuration/orchestrator/config_orchestrator.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <yaml-cpp/exceptions.h>
#include <yaml-cpp/node/convert.h>
#include <yaml-cpp/node/node.h>

#include <memory>
#include <optional>

#include "components/configuration/repository/config_loader.h"
#include "components/configuration/repository/config_repo.h"

using nextgen::engine::configuration::ConfigOrchestrator;
using nextgen::engine::configuration::ConfigRepository;
using ::testing::Return;

// Define mock configuration types

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes)
struct MockRenderingEngineConfig {
  int value;
  bool operator==(const MockRenderingEngineConfig& other) const {
    return value == other.value;
  }
};

struct MockVulkanConfig {
  int value;
  bool operator==(const MockVulkanConfig& other) const {
    return value == other.value;
  }
};
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes)

// YAML::convert specialization for MockRenderingEngineConfig and
// MockVulkanConfig
namespace YAML {

template <>
struct convert<MockRenderingEngineConfig> {
  // Encode MockRenderingEngineConfig to YAML::Node
  static Node encode(const MockRenderingEngineConfig& rhs) {
    Node node;
    node["value"] = rhs.value;
    return node;
  }

  // Decode YAML::Node to MockRenderingEngineConfig
  static bool decode(const Node& node, MockRenderingEngineConfig& rhs) {
    if (!node.IsMap() || !node["value"]) {
      return false;  // Invalid node structure
    }

    // Attempt to parse the 'value' field
    try {
      rhs.value = node["value"].as<int>();
    } catch (const YAML::BadConversion& e) {
      return false;  // Conversion failed
    }

    return true;
  }
};

template <>
struct convert<MockVulkanConfig> {
  // Encode MockVulkanConfig to YAML::Node
  static Node encode(const MockVulkanConfig& rhs) {
    Node node;
    node["value"] = rhs.value;
    return node;
  }

  // Decode YAML::Node to MockVulkanConfig
  static bool decode(const Node& node, MockVulkanConfig& rhs) {
    if (!node.IsMap() || !node["value"]) {
      return false;  // Invalid node structure
    }

    // Attempt to parse the 'value' field
    try {
      rhs.value = node["value"].as<int>();
    } catch (const YAML::BadConversion& e) {
      return false;  // Conversion failed
    }

    return true;
  }
};

}  // namespace YAML

// Mock ConfigLoader for testing
class MockConfigLoader : public nextgen::engine::configuration::IConfigLoader {
 public:
  MOCK_METHOD(YAML::Node, Load, (), (override));
  MOCK_METHOD(void, Save, (const YAML::Node* config), (override));
};

template <typename TConfigType>
struct TComponentEngine {
  using ConfigType = TConfigType;
  MOCK_METHOD(ConfigType, GetDefaultConfig, (), (const));
  MOCK_METHOD(std::optional<ConfigType>, ValidateConfig, (const ConfigType&),
              ());
  MOCK_METHOD(void, ApplyConfiguration, (const ConfigType&), ());
};

using MockRenderingEngine = TComponentEngine<MockRenderingEngineConfig>;
using MockVulkanRenderingApi = TComponentEngine<MockVulkanConfig>;

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes)
// Test fixture for ConfigOrchestrator
class ConfigOrchestratorTest : public ::testing::Test {
 protected:
  MockConfigLoader mock_loader;
  MockRenderingEngine mock_rendering_engine;
  MockVulkanRenderingApi mock_vulkan_api;
  std::unique_ptr<ConfigRepository>
      config_repo;  // Use unique_ptr for dynamic initialization

  void SetUp() override {
    // Initialize ConfigRepository within each test after setting up
    // expectations
  }

  void TearDown() override {
    // unique_ptr automatically cleans up
  }
};
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes)

namespace ConfigureCallsApplyConfigurationOnManagersWithValidConfigs {

TEST_F(ConfigOrchestratorTest,
       ConfigureCallsApplyConfigurationOnManagersWithValidConfigs) {
  // Define valid configurations
  MockRenderingEngineConfig rendering_config{100};
  MockVulkanConfig vulkan_config{200};

  // Set up the MockConfigLoader to return a YAML node with valid configurations
  YAML::Node root_config;
  root_config["rendering"]["value"] = rendering_config.value;
  root_config["rendering"]["vulkan"]["value"] = vulkan_config.value;

  // Expect Load() to be called twice (once for rendering, once for vulkan)
  EXPECT_CALL(mock_loader, Load()).WillOnce(Return(root_config));

  // Set up ValidateConfig to return the provided configurations
  EXPECT_CALL(mock_rendering_engine, ValidateConfig(rendering_config))
      .WillOnce(
          Return(std::optional<MockRenderingEngineConfig>(rendering_config)));
  EXPECT_CALL(mock_vulkan_api, ValidateConfig(vulkan_config))
      .WillOnce(Return(std::optional<MockVulkanConfig>(vulkan_config)));

  // Expect GetDefaultConfig not to be called
  EXPECT_CALL(mock_rendering_engine, GetDefaultConfig()).Times(0);
  EXPECT_CALL(mock_vulkan_api, GetDefaultConfig()).Times(0);

  // Expect ApplyConfiguration to be called with valid configurations
  EXPECT_CALL(mock_rendering_engine, ApplyConfiguration(rendering_config))
      .Times(1);
  EXPECT_CALL(mock_vulkan_api, ApplyConfiguration(vulkan_config)).Times(1);

  // Instantiate ConfigRepository after setting up expectations
  config_repo = std::make_unique<ConfigRepository>(mock_loader);

  // Instantiate ConfigOrchestrator
  ConfigOrchestrator<MockRenderingEngine, MockVulkanRenderingApi> orchestrator(
      *config_repo, mock_rendering_engine, mock_vulkan_api);

  // Call Configure to apply configurations
  orchestrator.Configure();
}

}  // namespace ConfigureCallsApplyConfigurationOnManagersWithValidConfigs

namespace ConfigureUsesDefaultConfigWhenValidConfigIsInvalid {
TEST_F(ConfigOrchestratorTest,
       ConfigureUsesDefaultConfigWhenValidConfigIsInvalid) {
  // Define invalid configurations
  MockRenderingEngineConfig const invalid_rendering_config{-1};
  MockVulkanConfig const invalid_vulkan_config{-2};

  // Define default configurations
  MockRenderingEngineConfig const default_rendering_config{42};
  MockVulkanConfig const default_vulkan_config{84};

  // Set up the MockConfigLoader to return a YAML node with invalid
  // configurations
  YAML::Node root_config;
  root_config["rendering"]["value"] = invalid_rendering_config.value;
  root_config["rendering"]["vulkan"]["value"] = invalid_vulkan_config.value;

  // Expect Load() to be called twice
  EXPECT_CALL(mock_loader, Load()).WillOnce(Return(root_config));

  // Set up ValidateConfig to return std::nullopt, indicating invalid
  // configurations
  EXPECT_CALL(mock_rendering_engine, ValidateConfig(invalid_rendering_config))
      .WillOnce(Return(std::nullopt));
  EXPECT_CALL(mock_vulkan_api, ValidateConfig(invalid_vulkan_config))
      .WillOnce(Return(std::nullopt));

  // Set up GetDefaultConfig to return default configurations
  EXPECT_CALL(mock_rendering_engine, GetDefaultConfig())
      .Times(1)
      .WillOnce(Return(default_rendering_config));
  EXPECT_CALL(mock_vulkan_api, GetDefaultConfig())
      .Times(1)
      .WillOnce(Return(default_vulkan_config));

  // Expect ApplyConfiguration to be called with default configurations
  EXPECT_CALL(mock_rendering_engine,
              ApplyConfiguration(default_rendering_config))
      .Times(1);
  EXPECT_CALL(mock_vulkan_api, ApplyConfiguration(default_vulkan_config))
      .Times(1);

  // Instantiate ConfigRepository after setting up expectations
  config_repo = std::make_unique<ConfigRepository>(mock_loader);

  // Instantiate ConfigOrchestrator
  ConfigOrchestrator<MockRenderingEngine, MockVulkanRenderingApi> orchestrator(
      *config_repo, mock_rendering_engine, mock_vulkan_api);

  // Call Configure to apply configurations
  orchestrator.Configure();
}

}  // namespace ConfigureUsesDefaultConfigWhenValidConfigIsInvalid

namespace ConfigureHandlesMixedValidAndInvalidConfigs {

TEST_F(ConfigOrchestratorTest, ConfigureHandlesMixedValidAndInvalidConfigs) {
  // Define a valid RenderingEngineConfig and an invalid VulkanConfig
  MockRenderingEngineConfig rendering_config{100};
  MockVulkanConfig const invalid_vulkan_config{-2};
  MockVulkanConfig const default_vulkan_config{84};

  // Set up the MockConfigLoader to return a YAML node with mixed configurations
  YAML::Node root_config;
  root_config["rendering"]["value"] = rendering_config.value;
  root_config["rendering"]["vulkan"]["value"] = invalid_vulkan_config.value;

  // Expect Load() to be called twice
  EXPECT_CALL(mock_loader, Load()).WillOnce(Return(root_config));

  // Set up ValidateConfig for RenderingEngine to return valid configuration
  EXPECT_CALL(mock_rendering_engine, ValidateConfig(rendering_config))
      .WillOnce(
          Return(std::optional<MockRenderingEngineConfig>(rendering_config)));

  // Set up ValidateConfig for VulkanRenderingApi to return std::nullopt
  EXPECT_CALL(mock_vulkan_api, ValidateConfig(invalid_vulkan_config))
      .WillOnce(Return(std::nullopt));

  // Set up GetDefaultConfig for VulkanRenderingApi to return default
  // configuration
  EXPECT_CALL(mock_vulkan_api, GetDefaultConfig())
      .Times(1)
      .WillOnce(Return(default_vulkan_config));

  // Expect ApplyConfiguration for RenderingEngine with valid configuration
  EXPECT_CALL(mock_rendering_engine, ApplyConfiguration(rendering_config))
      .Times(1);

  // Expect ApplyConfiguration for VulkanRenderingApi with default configuration
  EXPECT_CALL(mock_vulkan_api, ApplyConfiguration(default_vulkan_config))
      .Times(1);

  // Instantiate ConfigRepository after setting up expectations
  config_repo = std::make_unique<ConfigRepository>(mock_loader);

  // Instantiate ConfigOrchestrator
  ConfigOrchestrator<MockRenderingEngine, MockVulkanRenderingApi> orchestrator(
      *config_repo, mock_rendering_engine, mock_vulkan_api);

  // Call Configure to apply configurations
  orchestrator.Configure();
}

}  // namespace ConfigureHandlesMixedValidAndInvalidConfigs
