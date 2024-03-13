#include <gtest/gtest.h>

#include "ConfigManager.h"

class ConfigManagerTest : public ::testing::Test {
 protected:
  // Setup and teardown if needed
};

TEST_F(ConfigManagerTest, GetSetting_ReturnsCorrectValue) {
  // Assuming ConfigManager now has a constructor that takes a YAML string for
  // testing
  std::string testConfig = "audio:\n  volume: 75\n  muted: false\n";
  ConfigManager configManager(testConfig);  // Mocked or alternative constructor

  int volume = configManager.getSetting<int>("audio", "volume");
  bool muted = configManager.getSetting<bool>("audio", "muted");

  EXPECT_EQ(volume, 75);
  EXPECT_FALSE(muted);
}
