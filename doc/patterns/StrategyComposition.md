# Strategy composition

Let's integrate a RenderingConfigurationStrategy that encapsulates the overall configuration logic for the RenderComponent, which itself is composed of sub-components like VulkanComponent and DirectXComponent. This strategy will help orchestrate the configuration of all included sub-components, providing a unified interface for managing configuration while still allowing individual components to have their unique strategies.

## Step 1: Define a Common Strategy Interface

We'll start with a common interface for configuration strategies that includes a method to apply configurations. This will be used by both the main rendering strategy and the individual component strategies.

```cpp
class IConfigurationStrategy {
public:
    virtual ~IConfigurationStrategy() {}
    virtual void configure() = 0;
};
```

## Step 2: Implement Component-Specific Strategies

These strategies handle the specific details needed to configure each component within the rendering system.

```cpp
class VulkanConfigurationStrategy : public IConfigurationStrategy {
private:
    VulkanComponent& vulkanComponent_;

public:
    VulkanConfigurationStrategy(VulkanComponent& vulkanComponent)
        : vulkanComponent_(vulkanComponent) {}

    void configure() override {
        vulkanComponent_.applySettings();
    }
};

class DirectXConfigurationStrategy : public IConfigurationStrategy {
private:
    DirectXComponent& directXComponent_;

public:
    DirectXConfigurationStrategy(DirectXComponent& directXComponent)
        : directXComponent_(directXComponent) {}

    void configure() override {
        directXComponent_.applySettings();
    }
};
```

## Step 3: Implement the Rendering Configuration Strategy

This higher-level strategy uses the component-specific strategies to apply configurations to all relevant sub-components.

```cpp
class RenderingConfigurationStrategy : public IConfigurationStrategy {
private:
    VulkanConfigurationStrategy vulkanStrategy_;
    DirectXConfigurationStrategy directXStrategy_;

public:
    RenderingConfigurationStrategy(VulkanComponent& vulkanComponent, DirectXComponent& directXComponent)
        : vulkanStrategy_(vulkanComponent), directXStrategy_(directXComponent) {}

    void configure() override {
        vulkanStrategy_.configure();
        directXStrategy_.configure();
    }
};
```

## Step 4: Integration in the RenderComponent

The RenderComponent manages the higher-level configuration strategy and provides an interface to apply it.

```cpp
class RenderComponent {
private:
    VulkanComponent vulkanComponent_;
    DirectXComponent directXComponent_;
    RenderingConfigurationStrategy configurationStrategy_;

public:
    RenderComponent()
        : vulkanComponent_(), directXComponent_(),
          configurationStrategy_(vulkanComponent_, directXComponent_) {}

    void configure() {
        configurationStrategy_.configure();
    }
};
```

## Usage Example

Here’s how the system could be initialized and configured:

```cpp
int main() {
    RenderComponent renderComponent;
    renderComponent.configure();

    return 0;
}
```

## Conclusion

This approach provides a structured way to manage configurations in a system composed of various rendering sub-components. The RenderingConfigurationStrategy serves as an orchestrator that delegates the configuration tasks to the appropriate sub-component strategies. Each component maintains its configuration independence, while the overarching strategy ensures that the configurations are applied cohesively. This design enhances modularity, maintainability, and the ability to test each component independently or together as part of the whole system.
