# Facade

For the validation scenario where configuration validation depends not only on simple checks but also on complex conditions like device enumeration, resolution support checks, and checking for specific extensions and features supported by Vulkan devices—it's appropriate to use a combination of the Strategy Pattern and Facade Pattern. These patterns will help encapsulate the complexity of the Vulkan-specific checks and make the system both modular and extensible.

## Design Considerations

- **Strategy Pattern**: Continue using this for configuring and potentially for validation strategies to allow different validation rules or strategies to be swapped in as needed.
- **Facade Pattern**: Introduce a facade to abstract the complexity of interacting with Vulkan APIs for device enumeration and capability checks. This makes the system easier to manage and test.

## Step 1: Define the Validation Interface

Create an interface for validation strategies that can be used to implement different validation logic.

```cpp
class IConfigValidator {
public:
    virtual ~IConfigValidator() = default;
    virtual bool validate(const VulkanConfig& config, std::shared_ptr<VulkanInstance> instance) = 0;
};
```

## Step 2: Implement Concrete Validator

Implement a concrete validation class that encapsulates the logic required to validate the configuration against available Vulkan devices, supported resolutions, and required extensions.

```cpp
class VulkanConfigValidator : public IConfigValidator {
public:
    bool validate(const VulkanConfig& config, std::shared_ptr<VulkanInstance> instance) override {
        // Use VulkanInstance to enumerate devices
        auto devices = instance->enumerateDevices();

        // Check if the selected device and resolution support required extensions and features
        for (const auto& device : devices) {
            if (device.supportsConfig(config)) {
                return true;  // Valid configuration
            }
        }
        return false;  // Configuration is invalid
    }
};
```

## Step 3: Use the Validator in the Configuration Service

Integrate the validator into the configuration service or strategy, using it to validate the configuration after it's loaded and before it's applied.

```cpp
class FallbackConfigurationStrategy : public IConfigurationStrategy {
    std::shared_ptr<IConfigurationService> configService_;
    std::shared_ptr<IConfigValidator> configValidator_;
    std::shared_ptr<IConfigurationStrategy> defaultStrategy_;

public:
    FallbackConfigurationStrategy(std::shared_ptr<IConfigurationService> configService,
                                  std::shared_ptr<IConfigValidator> configValidator,
                                  std::shared_ptr<IConfigurationStrategy> defaultStrategy)
        : configService_(configService), configValidator_(configValidator), defaultStrategy_(defaultStrategy) {}

    void configure(std::shared_ptr<VulkanInstance> instance,
                   std::shared_ptr<VulkanDevice> device,
                   std::shared_ptr<VulkanSwap> swap) override {
        auto maybeConfig = configService_->loadConfig();
        if (maybeConfig.has_value() && configValidator_->validate(maybeConfig.value(), instance)) {
            // Configuration is valid, apply it
            VulkanConfig config = maybeConfig.value();
            device->configure(config);
            swap->configure(config);
        } else {
            // Fallback to default configuration if load fails or validation fails
            defaultStrategy_->configure(instance, device, swap);
        }
    }
};
```

## Step 4: Testing and Extensibility

With this design, each component can be independently tested. You can mock VulkanInstance and IConfigValidator to test the FallbackConfigurationStrategy under different scenarios, ensuring that it behaves correctly whether the configuration is valid, invalid, or fails to load.

This approach not only separates concerns but also provides the flexibility to replace or modify validation logic without impacting other parts of the system. The use of interfaces and dependency injection facilitates testing and maintenance, and the strategy pattern ensures that the system can adapt to future changes in validation requirements or strategies.
