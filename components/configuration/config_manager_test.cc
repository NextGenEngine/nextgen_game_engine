// #include <gtest/gtest.h>

// #include "config_manager.h"

// class ConfigManagerTest : public ::testing::Test {
// protected:
//   // Setup and teardown if needed
// };

// TEST_F(ConfigManagerTest, GetSetting_ReturnsCorrectValue) {
//   // Assuming ConfigManager now has a constructor that takes a YAML string
//   for
//   // testing
//   std::string testConfig = "audio:\n  volume: 75\n  muted: false\n";
//   ConfigManager configManager(testConfig); // Mocked or alternative
//   constructor

//   int volume = configManager.getSetting<int>("audio", "volume");
//   bool muted = configManager.getSetting<bool>("audio", "muted");

//   EXPECT_EQ(volume, 75);
//   EXPECT_FALSE(muted);
// }

#include "components/configuration/config_manager.h"  // Adjust include path as necessary

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Return;

class MockConfigLoader : public IConfigLoader {
 public:
  MOCK_METHOD(YAML::Node, load, (const std::string &), (override));
};

TEST(ConfigManagerTest, SuccessfullyLoadsConfig) {
  auto mockLoader = std::make_unique<NiceMock<MockConfigLoader>>();
  YAML::Node fakeNode;
  fakeNode["database"]["host"] = "localhost";

  EXPECT_CALL(*mockLoader, load(_)).WillOnce(Return(fakeNode));

  ConfigManager manager(std::move(mockLoader), "dummy/path");
  auto host = manager.getSetting<std::string>("database", "host");

  EXPECT_EQ(host, "localhost");
}

TEST(ConfigManagerTest, ThrowsExceptionWhenFileNotFound) {
  auto mockLoader = std::make_unique<NiceMock<MockConfigLoader>>();

  // Ensure the method name matches what's declared in IConfigLoader. Adjust
  // "load" as necessary.
  EXPECT_CALL(*mockLoader, load(_))
      .WillOnce([](const std::string &) -> YAML::Node {
        throw std::runtime_error("File not found");
      });

  // Since ConfigManager expects a std::unique_ptr<IConfigLoader>, we use
  // std::move to transfer ownership.
  EXPECT_THROW(
      { ConfigManager manager(std::move(mockLoader), "non/existent/path"); },
      std::runtime_error);
}
