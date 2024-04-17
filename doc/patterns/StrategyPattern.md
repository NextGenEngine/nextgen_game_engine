# Strategy pattern example

To implement the DefaultConfigurationStrategy that utilizes the VulkanInstance::GetDefaultConfig method to configure both VulkanDevice and VulkanSwap, and then saves this configuration using a ConfigurationService, we'll write an example that covers these requirements. This approach assumes the existence of methods and interfaces.

## Required Classes and Methods

- **VulkanInstance::GetDefaultConfig**: Retrieves default configuration settings necessary for initializing other components.
- **VulkanDevice**::configure: Applies configuration settings.
- **VulkanSwap**::configure: Applies configuration settings.
- **ConfigurationService**::saveConfig: Persists configuration settings.

## Example Implementation

First, define the configuration strategy and configuration service interfaces and classes:

```cpp
#include <memory>

class VulkanConfig {
public:
    // Add configuration parameters as needed
};

class VulkanInstance {
public:
    VulkanConfig GetDefaultConfig() {
        // Return default Vulkan configuration
        return VulkanConfig();
    }
};

class VulkanDevice {
public:
    void configure(const VulkanConfig& config) {
        // Apply configuration to VulkanDevice
    }
};

class VulkanSwap {
public:
    void configure(const VulkanConfig& config) {
        // Apply configuration to VulkanSwap
    }
};

class IConfigurationService {
public:
    virtual void saveConfig(const VulkanConfig& config) = 0;
};

class ConfigurationService : public IConfigurationService {
public:
    void saveConfig(const VulkanConfig& config) override {
        // Implement logic to save the config
    }
};

class VulkanRenderingApi {
public:
    VulkanRenderingApi(std::shared_ptr<VulkanInstance> instance,
                       std::shared_ptr<VulkanDevice> device,
                       std::shared_ptr<VulkanSwap> swap)
        : instance_(instance), device_(device), swap_(swap) {}

    void configure(IConfigurationStrategy& strategy) {
        strategy.configure(instance_, device_, swap_);
    }

private:
    std::shared_ptr<VulkanInstance> instance_;
    std::shared_ptr<VulkanDevice> device_;
    std::shared_ptr<VulkanSwap> swap_;
};

class IConfigurationStrategy {
public:
    virtual ~IConfigurationStrategy() = default;
    virtual void configure(std::shared_ptr<VulkanInstance> instance,
                           std::shared_ptr<VulkanDevice> device,
                           std::shared_ptr<VulkanSwap> swap) = 0;
};

class DefaultConfigurationStrategy : public IConfigurationStrategy {
    std::shared_ptr<IConfigurationService> configService_;

public:
    DefaultConfigurationStrategy(std::shared_ptr<IConfigurationService> configService)
        : configService_(configService) {}

    void configure(std::shared_ptr<VulkanInstance> instance,
                   std::shared_ptr<VulkanDevice> device,
                   std::shared_ptr<VulkanSwap> swap) override {
        VulkanConfig config = instance->GetDefaultConfig();
        device->configure(config);
        swap->configure(config);
        configService_->saveConfig(config); // Save configuration after applying
    }
};
```

## Integration Example

Here’s how you could use these classes together:

```cpp
int main() {
    auto instance = std::make_shared<VulkanInstance>();
    auto device = std::make_shared<VulkanDevice>();
    auto swap = std::make_shared<VulkanSwap>();
    auto configService = std::make_shared<ConfigurationService>();
    auto strategy = std::make_shared<DefaultConfigurationStrategy>(configService);

    VulkanRenderingApi api(instance, device, swap);
    api.configure(*strategy);

    return 0;
}
```

## Conclusion

This setup uses the Strategy Pattern to allow for flexible configuration of the Vulkan API components based on a default configuration retrieved from VulkanInstance. It enables changing configuration logic without altering the client code or the components being configured. The configuration is then saved using a ConfigurationService, encapsulating the persistence logic separately from the configuration logic, adhering to the Single Responsibility Principle. This design makes the system more maintainable, testable, and extensible.
