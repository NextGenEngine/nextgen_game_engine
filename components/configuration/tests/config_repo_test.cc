#include "components/configuration/repository/config_repo.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <yaml-cpp/node/emit.h>
#include <yaml-cpp/node/node.h>

#include <string>

#include "components/configuration/repository/config_loader.h"

using nextgen::engine::configuration::ConfigRepository;
using nextgen::engine::configuration::ConfigRepositoryNode;

// Mock ConfigLoader for testing
class MockConfigLoader : public nextgen::engine::configuration::IConfigLoader {
 public:
  MOCK_METHOD(YAML::Node, Load, (), (override));
  MOCK_METHOD(void, Save, (const YAML::Node* config), (override));
};

namespace LoadsConfigurationSuccessfullyTest {

// LoadsConfigurationSuccessfully test
constexpr auto APP_NAME_SECTION = "app_name";
constexpr auto APP_NAME = "MyGame";
constexpr auto VERSION_SECTION = "version";
constexpr auto VERSION = "1.0";

TEST(ConfigRepositoryTest, LoadsConfigurationSuccessfully) {
  // Create a mock loader instance
  MockConfigLoader mockLoader;

  // Define expected configuration
  YAML::Node expectedConfig;
  expectedConfig[APP_NAME_SECTION] = APP_NAME;
  expectedConfig[VERSION_SECTION] = VERSION;

  // Set up the mock to return the expected configuration
  EXPECT_CALL(mockLoader, Load())
      .Times(1)
      .WillOnce(::testing::Return(expectedConfig));

  // Instantiate ConfigRepository with the mock loader
  ConfigRepository configManager(mockLoader);

  // Load the configuration
  YAML::Node config = configManager.GetYamlNode();

  // Verify that the configuration matches the expected values
  EXPECT_EQ(config[APP_NAME_SECTION].as<std::string>(), APP_NAME);
  EXPECT_EQ(config[VERSION_SECTION].as<std::string>(), VERSION);
}

}  // namespace LoadsConfigurationSuccessfullyTest

namespace GetNodeReturnsCorrectNodeTest {

// GetNodeReturnsCorrectNode test
constexpr auto EXISTING_COMPONENT_SECTION = "existing_component";
constexpr auto SETTING_SECTION = "setting";
constexpr auto SETTING_VALUE = "value";
constexpr auto NEW_COMPONENT_SECTION = "new_component";

TEST(ConfigRepositoryTest, GetNodeReturnsCorrectNode) {
  // Create a mock loader instance
  MockConfigLoader mockLoader;

  // Define initial configuration
  YAML::Node initialConfig;
  initialConfig[EXISTING_COMPONENT_SECTION][SETTING_SECTION] = SETTING_VALUE;

  // Set up the mock to return the initial configuration
  EXPECT_CALL(mockLoader, Load())
      .Times(1)
      .WillOnce(::testing::Return(initialConfig));

  // Instantiate ConfigRepository with the mock loader
  ConfigRepository configManager(mockLoader);

  // Request a component configuration for an existing component
  ConfigRepositoryNode const existingConfigRepositoryNode =
      configManager.GetNode(EXISTING_COMPONENT_SECTION);

  // Verify that the retrieved node contains the correct data
  const YAML::Node& existingNode = existingConfigRepositoryNode.GetYamlNode();
  EXPECT_EQ(existingNode[SETTING_SECTION].as<std::string>(), SETTING_VALUE);

  // Request a component configuration for a non-existing component
  ConfigRepositoryNode const newConfigRepositoryNode =
      configManager.GetNode(NEW_COMPONENT_SECTION);

  // Verify that the new node is created
  const YAML::Node& newNode = newConfigRepositoryNode.GetYamlNode();
  EXPECT_TRUE(newNode.IsDefined());

  // Since newConfigRepositoryNode[NEW_COMPONENT_SECTION] didn't exist, its node
  // should be empty and Map by default
  EXPECT_TRUE(newNode.IsMap());
  EXPECT_EQ(newNode.size(), 0);
}

}  // namespace GetNodeReturnsCorrectNodeTest

namespace NestedConfigRepositoryNodeSaveWorksCorrectlyTest {

// NestedConfigRepositoryNodeSaveWorksCorrectly test
constexpr auto RENDERING_SECTION = "rendering";
constexpr auto VULKAN_SECTION = "vulkan";
constexpr auto VULKAN_VERSION_SECTION = "api_version";
constexpr auto VULKAN_VERSION = "1.2";
constexpr auto RENDERING_API_SECTION = "api";
constexpr auto RENDERING_API_NAME = "Vulkan";

TEST(ConfigRepositoryTest, NestedConfigRepositoryNodeSaveWorksCorrectly) {
  // Create a mock loader instance
  MockConfigLoader mockLoader;

  // Define initial empty configuration
  YAML::Node const initialConfig;  // Empty YAML

  // Set up the mock to return the initial empty configuration
  EXPECT_CALL(mockLoader, Load())
      .Times(1)
      .WillOnce(::testing::Return(initialConfig));

  // Capture the saved configuration
  YAML::Node savedConfig;
  EXPECT_CALL(mockLoader, Save(::testing::_))
      .Times(1)
      .WillOnce(::testing::Invoke(
          [&savedConfig](const YAML::Node* config) { savedConfig = *config; }));

  // Instantiate ConfigRepository with the mock loader
  ConfigRepository configManager(mockLoader);

  // Get the rendering component configuration
  ConfigRepositoryNode renderingComponent =
      configManager.GetNode(RENDERING_SECTION);
  renderingComponent.GetYamlNodeMutable()[RENDERING_API_SECTION] =
      RENDERING_API_NAME;

  // Get the vulkan component configuration from rendering
  ConfigRepositoryNode vulkanComponent =
      renderingComponent.GetNode(VULKAN_SECTION);

  // Optionally, modify the vulkan component configuration
  YAML::Node& vulkanNode = vulkanComponent.GetYamlNodeMutable();
  vulkanNode[VULKAN_VERSION_SECTION] = VULKAN_VERSION;

  // Save the configuration
  vulkanComponent.Save();

  // Verify that the saved configuration matches the expected structure
  YAML::Node expectedConfig;
  expectedConfig[RENDERING_SECTION][RENDERING_API_SECTION] = RENDERING_API_NAME;
  expectedConfig[RENDERING_SECTION][VULKAN_SECTION][VULKAN_VERSION_SECTION] =
      VULKAN_VERSION;

  // Compare the saved configuration with the expected configuration
  EXPECT_EQ(YAML::Dump(savedConfig), YAML::Dump(expectedConfig));
  EXPECT_EQ(
      savedConfig[RENDERING_SECTION][VULKAN_SECTION][VULKAN_VERSION_SECTION]
          .as<std::string>(),
      VULKAN_VERSION);
  EXPECT_EQ(
      savedConfig[RENDERING_SECTION][RENDERING_API_SECTION].as<std::string>(),
      RENDERING_API_NAME);
}

}  // namespace NestedConfigRepositoryNodeSaveWorksCorrectlyTest

namespace LoadAndUpdateConfigWorksCorrectlyTest {

#include <cstdint>
#include <optional>

struct VulkanConfig {
  uint32_t device_id;  // ID for the physical device (GPU) to be used
  uint32_t width;      // Width of the window or surface
  uint32_t height;     // Height of the window or surface
  float refresh_rate;  // Refresh rate in Hz
};

TEST(ConfigRepositoryNodeTest, LoadAndUpdateConfigWorksCorrectly) {
  // Create a mock loader instance
  MockConfigLoader mockLoader;

  // Define initial configuration
  YAML::Node initialConfig;
  initialConfig["device_id"] = 1;
  initialConfig["width"] = 1920;
  initialConfig["height"] = 1080;
  initialConfig["refresh_rate"] = 60.0F;
  initialConfig["unknown"] = "unknown";

  // Set up the mock to return the initial configuration
  EXPECT_CALL(mockLoader, Load())
      .Times(1)
      .WillOnce(::testing::Return(YAML::Node()));

  // Capture the saved configuration
  YAML::Node savedConfig;
  EXPECT_CALL(mockLoader, Save(::testing::_))
      .Times(1)
      .WillOnce(::testing::Invoke(
          [&savedConfig](const YAML::Node* config) { savedConfig = *config; }));

  // Instantiate ConfigRepository with the mock loader
  ConfigRepository configManager(mockLoader);

  // Get the Vulkan component configuration
  ConfigRepositoryNode renderingComponent = configManager.GetNode("rendering");
  ConfigRepositoryNode vulkanComponent = configManager.GetNode("vulkan");

  // Set rendering api to Vulkan to test that UpdateConfig does not rewrite
  // unknown properties
  renderingComponent.GetYamlNodeMutable()["api"] = "Vulkan";

  // Update the component node with initial configuration
  vulkanComponent.GetYamlNodeMutable() = initialConfig;

  // Load the configuration into a VulkanConfig struct
  std::optional<VulkanConfig> vulkanConfigOpt =
      vulkanComponent.LoadConfig<VulkanConfig>();

  // Verify that the VulkanConfig struct is loaded correctly
  ASSERT_TRUE(vulkanConfigOpt.has_value());
  if (vulkanConfigOpt.has_value()) {
    VulkanConfig vulkanConfig = vulkanConfigOpt.value();
    EXPECT_EQ(vulkanConfig.device_id, 1);
    EXPECT_EQ(vulkanConfig.width, 1920U);
    EXPECT_EQ(vulkanConfig.height, 1080U);
    EXPECT_FLOAT_EQ(vulkanConfig.refresh_rate, 60.0F);
    // Modify the VulkanConfig struct
    vulkanConfig.device_id = 2;
    vulkanConfig.width = 2560;
    vulkanConfig.height = 1440;
    vulkanConfig.refresh_rate = 144.0F;

    // Update the ConfigRepositoryNode with the modified VulkanConfig
    vulkanComponent.UpdateConfig(vulkanConfig);
    // Save the configuration
    vulkanComponent.Save();
  }

  // Verify that the saved configuration matches the modified VulkanConfig
  EXPECT_EQ(savedConfig["vulkan"]["device_id"].as<uint32_t>(), 2U);
  EXPECT_EQ(savedConfig["vulkan"]["width"].as<uint32_t>(), 2560U);
  EXPECT_EQ(savedConfig["vulkan"]["height"].as<uint32_t>(), 1440U);
  EXPECT_FLOAT_EQ(savedConfig["vulkan"]["refresh_rate"].as<float>(), 144.0F);
  EXPECT_EQ(savedConfig["vulkan"]["unknown"].as<std::string>(), "unknown");
  EXPECT_EQ(savedConfig["rendering"]["api"].as<std::string>(), "Vulkan");
}

}  // namespace LoadAndUpdateConfigWorksCorrectlyTest

namespace YAML {

using LoadAndUpdateConfigWorksCorrectlyTest::VulkanConfig;
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

namespace CopyConstructorWorksCorrectlyTest {

TEST(ConfigRepositoryNodeTest, CopyConstructorWorksCorrectly) {
  // Create a mock loader instance
  MockConfigLoader mockLoader;

  // Define initial configuration
  YAML::Node initialConfig;
  initialConfig["device_id"] = 1;

  // Set up the mock to return the initial configuration
  EXPECT_CALL(mockLoader, Load())
      .Times(1)
      .WillOnce(::testing::Return(initialConfig));

  // Instantiate ConfigRepository with the mock loader
  ConfigRepository configManager(mockLoader);

  // Get the Vulkan component configuration
  ConfigRepositoryNode originalComponent = configManager.GetNode("vulkan");

  // Modify the original component
  originalComponent.GetYamlNodeMutable()["width"] = 1920;

  // Copy the original component to a new component
  ConfigRepositoryNode copiedComponent =
      originalComponent;  // Uses copy constructor

  // Verify that the copied component has the same node values as the original
  EXPECT_EQ(copiedComponent.GetYamlNode()["width"].as<int>(), 1920);

  // Ensure that both original and copied components share the same
  // ConfigRepository
  EXPECT_EQ(&(copiedComponent.GetConfigRepository()),
            &(originalComponent.GetConfigRepository()));

  // Now lets modify original and expect this change in copy, and also do it
  // vise versa
  originalComponent.GetYamlNodeMutable()["width"] = 762;
  EXPECT_EQ(copiedComponent.GetYamlNode()["width"].as<int>(), 762);
  copiedComponent.GetYamlNodeMutable()["width"] = 2560;
  EXPECT_EQ(originalComponent.GetYamlNode()["width"].as<int>(), 2560);
}

}  // namespace CopyConstructorWorksCorrectlyTest
