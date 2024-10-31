#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <optional>

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes)
// Define a mock configuration type
struct MockConfig {
  int value;
  bool operator==(const MockConfig& other) const {
    return value == other.value;
  }
};
// NOLINTEND(misc-non-private-member-variables-in-classes,cppcoreguidelines-non-private-member-variables-in-classes)

// Define a mock engine component that satisfies the EngineComponentTypeConcept
struct MockEngineComponentType {
  using ConfigType = MockConfig;
  // Mock the methods required by the concept
  MOCK_METHOD(MockConfig, GetDefaultConfig, (), ());
  MOCK_METHOD(std::optional<MockConfig>, ValidateConfig, (const MockConfig&),
              ());
  MOCK_METHOD(void, ApplyConfiguration, (const MockConfig&), ());
};

#include "components/configuration/managers/config_manager_template.h"

using nextgen::engine::configuration::ConfigComponentManager;
using ::testing::_;
using ::testing::Return;

struct ConfigComponentManagerTest : public ::testing::Test {
 protected:
  MockEngineComponentType mock_component;
};

namespace DefaultConfigIsLoadedWhenNoConfigProvided {

TEST_F(ConfigComponentManagerTest, DefaultConfigIsLoadedWhenNoConfigProvided) {
  // Set up expectations
  MockConfig default_config{42};
  EXPECT_CALL(mock_component, GetDefaultConfig())
      .WillOnce(Return(default_config));

  // Instantiate ConfigComponentManager with std::nullopt
  ConfigComponentManager<MockEngineComponentType> manager(mock_component,
                                                          std::nullopt);

  // The config_wrapper_ should have is_default == true
  EXPECT_TRUE(manager.GetConfigWrapperRef().is_default);

  // The config should be the default config
  EXPECT_EQ(manager.GetConfigRef().value, 42);

  // Expect ApplyConfiguration to be called once with the default config
  EXPECT_CALL(mock_component, ApplyConfiguration(default_config)).Times(1);

  // Call ConfigureComponent to apply the configuration
  manager.ConfigureComponent();

  // Subsequent calls should not call ApplyConfiguration since modified is now
  // false
  EXPECT_CALL(mock_component, ApplyConfiguration(_)).Times(0);
  manager.ConfigureComponent();
}

}  // namespace DefaultConfigIsLoadedWhenNoConfigProvided

namespace ProvidedValidConfigIsUsed {

TEST_F(ConfigComponentManagerTest, ProvidedValidConfigIsUsed) {
  MockConfig provided_config{100};

  // Expect ValidateConfig to return the provided config (valid)
  EXPECT_CALL(mock_component, ValidateConfig(provided_config))
      .WillOnce(Return(provided_config));

  // Instantiate ConfigComponentManager with the provided valid config
  ConfigComponentManager<MockEngineComponentType> manager(mock_component,
                                                          provided_config);

  // is_default should be false since we provided a valid config
  EXPECT_FALSE(manager.GetConfigWrapperRef().is_default);

  // The config should be the provided config
  EXPECT_EQ(manager.GetConfigRef().value, 100);

  // Expect ApplyConfiguration to be called once with the provided config
  EXPECT_CALL(mock_component, ApplyConfiguration(provided_config)).Times(1);
  manager.ConfigureComponent();
}

}  // namespace ProvidedValidConfigIsUsed

namespace ProvidedInvalidConfigLoadsDefault {

TEST_F(ConfigComponentManagerTest, ProvidedInvalidConfigLoadsDefault) {
  MockConfig invalid_config{-1};

  // Expect ValidateConfig to return std::nullopt (invalid config)
  EXPECT_CALL(mock_component, ValidateConfig(invalid_config))
      .WillOnce(Return(std::nullopt));

  // Expect GetDefaultConfig to be called and return default config
  MockConfig default_config{42};
  EXPECT_CALL(mock_component, GetDefaultConfig())
      .WillOnce(Return(default_config));

  // Instantiate ConfigComponentManager with the invalid config
  ConfigComponentManager<MockEngineComponentType> manager(mock_component,
                                                          invalid_config);

  // Since the provided config is invalid, is_default should be true
  EXPECT_TRUE(manager.GetConfigWrapperRef().is_default);

  // The config should be the default config
  EXPECT_EQ(manager.GetConfigRef().value, 42);

  // Expect ApplyConfiguration to be called once with the default config
  EXPECT_CALL(mock_component, ApplyConfiguration(default_config)).Times(1);
  manager.ConfigureComponent();
}

}  // namespace ProvidedInvalidConfigLoadsDefault

namespace ModifiedPropertyControlsApplyConfiguration {

TEST_F(ConfigComponentManagerTest, ModifiedPropertyControlsApplyConfiguration) {
  MockConfig initial_config{100};

  // Expect ValidateConfig to return the initial config (valid)
  EXPECT_CALL(mock_component, ValidateConfig(initial_config))
      .WillOnce(Return(initial_config));

  // Instantiate ConfigComponentManager with the initial valid config
  ConfigComponentManager<MockEngineComponentType> manager(mock_component,
                                                          initial_config);

  // Expect ApplyConfiguration to be called once with the initial config
  EXPECT_CALL(mock_component, ApplyConfiguration(initial_config)).Times(1);
  manager.ConfigureComponent();

  // Subsequent calls should not call ApplyConfiguration since modified is now
  // false
  EXPECT_CALL(mock_component, ApplyConfiguration(_)).Times(0);
  manager.ConfigureComponent();

  // Now, set a new configuration
  MockConfig new_config{200};
  EXPECT_CALL(mock_component, ValidateConfig(new_config))
      .WillOnce(Return(std::optional<MockConfig>(new_config)));

  manager.SetConfiguration(new_config);

  // Expect ApplyConfiguration to be called again with the new config
  EXPECT_CALL(mock_component, ApplyConfiguration(new_config)).Times(1);
  manager.ConfigureComponent();

  // modified is now false again; subsequent calls should not call
  // ApplyConfiguration
  EXPECT_CALL(mock_component, ApplyConfiguration(_)).Times(0);
  manager.ConfigureComponent();
}

}  // namespace ModifiedPropertyControlsApplyConfiguration
