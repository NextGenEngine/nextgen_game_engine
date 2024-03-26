#include "components/configuration/config_manager.h"

#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>
#include <string>

TEST(ConfigManagerTest, GetSettingFromFile) {
  // Create a temporary YAML file for testing
  std::ofstream file("test_config.yaml");
  file << "module:\n";
  file << "  setting: 42\n";
  file.close();

  // Load the configuration from the file
  ConfigManager manager = ConfigManager_File("test_config.yaml");

  // Test retrieving a setting
  EXPECT_EQ(manager.getSetting<int>("module", "setting"), 42);

  // Clean up the temporary file
  std::remove("test_config.yaml");
}

TEST(ConfigManagerTest, GetSettingFromString) {
  // YAML content for testing
  std::string const yamlContent = "module:\n  setting: 42\n";

  // Load the configuration from the string
  ConfigManager manager = ConfigManager_String(yamlContent);

  // Test retrieving a setting
  EXPECT_EQ(manager.getSetting<int>("module", "setting"), 42);
}
