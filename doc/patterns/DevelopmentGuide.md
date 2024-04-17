# Patters used in NextGenGameEngine

## Requirements

So. i have VulkanRenderingApi component. it has 4 subcomponents (injected as dependencies as private members): context, instance, device, swap.

i can't get default configuration, unless "context" and "instance" components are initialized , because to get default configuration I need to enumerate 3d-devices in the system using context and instance (which depends on context) components. and after that I want to save my default configuration using configuration service.

what set of patterns to use to implement this flow? i need robust extensible and testable system. easy readable code, highly structural and very well organized

## Solution

To implement the flow you described, ensuring a robust, extensible, and testable system, you'll want to use a combination of design patterns that complement each other to handle dependency injection, lifecycle management, and configuration handling efficiently. Here's a structured approach to design your VulkanRenderingApi component:

## 1. Constructor Injection for Dependencies

Utilize the Dependency Injection pattern to manage dependencies among context, instance, device, and swap components. This will help in managing the lifecycle of dependencies more cleanly and allow for easier unit testing.

```cpp
class VulkanContext;
class VulkanInstance;
class VulkanDevice;
class VulkanSwap;

class VulkanRenderingApi {
public:
    VulkanRenderingApi(
        std::shared_ptr<VulkanContext> context,
        std::shared_ptr<VulkanInstance> instance,
        std::shared_ptr<VulkanDevice> device,
        std::shared_ptr<VulkanSwap> swap)
        : context_(context), instance_(instance), device_(device), swap_(swap) {}

    void initialize();
private:
    std::shared_ptr<VulkanContext> context_;
    std::shared_ptr<VulkanInstance> instance_;
    std::shared_ptr<VulkanDevice> device_;
    std::shared_ptr<VulkanSwap> swap_;
};
```

## 2. Factory Pattern for Object Creation

Use the Factory Pattern to encapsulate the creation logic of the Vulkan components, which might involve complex initializations that depend on one another.

```cpp
class VulkanComponentFactory {
public:
    std::shared_ptr<VulkanContext> createContext();
    std::shared_ptr<VulkanInstance> createInstance(std::shared_ptr<VulkanContext> context);
    std::shared_ptr<VulkanDevice> createDevice(std::shared_ptr<VulkanInstance> instance);
    std::shared_ptr<VulkanSwap> createSwap(std::shared_ptr<VulkanDevice> device);
};
```

## 3. Builder Pattern for Managing Complex Construction

Considering the dependency between context, instance, device, and swap, use the Builder Pattern to manage their construction and the eventual creation of the VulkanRenderingApi object.

```cpp
class VulkanRenderingApiBuilder {
public:
    VulkanRenderingApiBuilder& withContext();
    VulkanRenderingApiBuilder& withInstance();
    VulkanRenderingApiBuilder& withDevice();
    VulkanRenderingApiBuilder& withSwap();

    std::shared_ptr<VulkanRenderingApi> build();

private:
    VulkanComponentFactory factory_;
    std::shared_ptr<VulkanContext> context_;
    std::shared_ptr<VulkanInstance> instance_;
    std::shared_ptr<VulkanDevice> device_;
    std::shared_ptr<VulkanSwap> swap_;
};
```

## 4. Strategy Pattern for Configuration Management

To handle different configurations, especially post-initialization with context and instance, use the Strategy Pattern. This will allow the VulkanRenderingApi to change its configuration strategy at runtime.

```cpp
class IConfigurationStrategy {
public:
    virtual ~IConfigurationStrategy() = default;
    virtual void configure(std::shared_ptr<VulkanRenderingApi> api) = 0;
};

class DefaultConfigurationStrategy : public IConfigurationStrategy {
public:
    void configure(std::shared_ptr<VulkanRenderingApi> api) override {
        // Implementation for default configuration
    }
};

class CustomConfigurationStrategy : public IConfigurationStrategy {
public:
    void configure(std::shared_ptr<VulkanRenderingApi> api) override {
        // Custom configuration logic
    }
};
```

## 5. Observer Pattern for Reactive Configuration

Use the Observer Pattern if configuration needs to be updated reactively based on changes in the system or user inputs.

**_Integration Example_**

```cpp
// Assuming each method of VulkanRenderingApiBuilder initializes the respective components.
VulkanRenderingApiBuilder builder;
auto vulkanApi = builder.withContext()
                         .withInstance()
                         .withDevice()
                         .withSwap()
                         .build();

DefaultConfigurationStrategy configStrategy;
configStrategy.configure(vulkanApi);
```

// Now, vulkanApi is fully configured and ready to use
Conclusion
By integrating these patterns, you create a system that is not only robust and testable but also highly extensible. Dependency injection facilitates easier testing and maintenance, the factory and builder patterns manage complex creation logic, and the strategy pattern provides flexible configuration management. Each component can be developed, tested, and maintained independently or integrated seamlessly.
