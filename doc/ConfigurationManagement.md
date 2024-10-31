# Configuration management subsystem

Designing a Centralized Configuration System for NextGen Game Engine

---

## Requirements

This configuration system provides a centralized approach where:

- Each engine component has a dedicated configuration structure.
- Configurations are aggregated into a central repository, organized as a hierarchical tree.
- Components remain agnostic about the configuration storage location, interacting only with their own configuration structures.
- Changes to configurations are automatically applied to the relevant components.
- The system is designed for modularity, extensibility, and clarity, following best practices in C++.

The solution includes:

1. **Central Configuration Repository**: Manages the configuration tree, loads, saves, and provides access to configuration nodes.
2. **Component Configuration Structures**: Each component (e.g., `RenderingEngine`, `VulkanRenderingApi`) has its own configuration structure, reflecting only the data it needs.
3. **Template-Based Component Managers**: Each component has a configuration manager that loads, updates, and applies the component’s configuration. Managers use a templated `ConfigComponentManager` base, allowing easy extension to other components.
4. **Configuration Orchestrator**: A central orchestrator applies configurations to components in the correct dependency order and ensures that configurations are propagated across interdependent components.
5. **Hardcoded Configuration Tree**: The configuration tree structure is explicitly defined, which improves performance by avoiding dynamic allocations and enhances code clarity by making dependencies clear.

---

## Solution Components

1. **Central Configuration Repository (`ConfigRepository` and `ConfigRepositoryNode`)**

   - The `ConfigRepository` serves as the root for accessing all configurations, loading data from sources like files or strings via `ConfigLoader` implementations (e.g., `FileLoader`).
   - `ConfigRepositoryNode` allows access to specific sections of the configuration tree, enabling components to retrieve, update, and save configurations for their sub-tree without knowledge of other sections.
   - Each node in the tree represents a configuration section (e.g., `rendering`, `rendering.vulkan`) and provides methods for loading or updating specific configurations.

2. **Component-Specific Configuration Structures**

   - Each component has a distinct configuration structure (e.g., `RenderingEngineConfig`, `VulkanConfig`), which defines the exact data fields required by the component.
   - These structures are registered in the configuration tree and can be loaded, updated, and applied without requiring modifications to the central configuration system.

3. **Template-Based Component Managers (`ConfigComponentManager`)**

   - The `ConfigComponentManager` is a templated base class that each component-specific manager inherits.
   - Each derived manager, such as `RenderingEngineConfigManager` and `VulkanRenderingApiConfigManager`, provides component-specific logic while using the base’s common interface for loading, storing, and applying configurations.
   - The `ConfigWithDefaultFlag` struct encapsulates configuration data with a default flag, which marks whether a configuration is set by the user or is using a default value.

4. **Configuration Orchestrator (`ConfigOrchestrator`)**

   - The `ConfigOrchestrator` oversees the initialization and application of configurations to all components, handling dependencies and ensuring the configurations are applied in the correct order.
   - By centralizing control, the orchestrator provides flexibility in how configurations are applied (e.g., it can reinitialize components when a major configuration change, like switching rendering APIs, occurs).
   - It operates by coordinating the configuration managers for different components, updating configurations from the central repository, and applying them to the components.

5. **Hardcoded Configuration Tree**
   - The configuration tree is explicitly defined in the configuration code, allowing direct access to specific configuration paths (e.g., `rendering`, `rendering.vulkan`).
   - This hardcoded structure avoids the overhead of dynamic memory allocation and facilitates faster access, which is especially useful for high-performance requirements in game engines.

---

## How to Use

1. **Initialize the Configuration System**:

   - Set up a `ConfigRepository` with a loader (e.g., `FileLoader` to load from a YAML file).
   - Create an instance of each component’s configuration manager, passing the relevant section of the configuration tree to each.

2. **Load and Apply Configurations**:

   - Each component manager (`ConfigComponentManager`) loads its configuration section from `ConfigRepository`.
   - Use the `ConfigOrchestrator` to apply all configurations in the correct order, ensuring dependencies are respected.

3. **Update Configurations**:
   - When configurations change (e.g., due to user input in the UI), update the configuration in the corresponding manager without directly affecting the component.
   - The `ConfigOrchestrator` can then reapply configurations as needed to ensure components remain in sync with the latest settings.

---

This design achieves modularity, performance, and simplicity, allowing new configurations to be added or modified with minimal impact on other components. The use of template-based managers and the configuration orchestrator provides fine-grained control over configuration management and application order. This approach is ideal for managing complex, interdependent configurations in a high-performance engine.

### Usage Overview

1. **Initializing the Configuration System**:

   - Create a `ConfigRepository` instance with a specified loader (e.g., `FileLoader`) to access configurations from a file or string.
   - Use `ConfigRepositoryNode` objects obtained from `ConfigRepository` to access specific configuration sections for various components.

2. **Loading and Applying Configurations**:

   - For each component (e.g., `RenderingEngine`), create an associated configuration manager (e.g., `RenderingEngineConfigManager`).
   - Use the configuration manager to load configurations via `LoadConfig` and apply them via `SetConfiguration`.

3. **Using ConfigOrchestrator for Centralized Control**:

   - Instantiate `ConfigOrchestrator` with references to `ConfigRepository` and the relevant engine components (e.g., `RenderingEngine`).
   - Call `Configure` on the orchestrator to apply configurations to all components in the correct order based on dependencies.

4. **Runtime Configuration Updates**:
   - When configurations are modified, either in code or through UI interactions, update the respective `ConfigComponentManager`.
   - The orchestrator can then reapply configurations as necessary, handling any dependent reinitializations (e.g., switching between rendering APIs).

---

### Example Workflow

```cpp
#include "components/configuration/repository/config_repo.h"
#include "components/configuration/orchestrator/config_orchestrator_template.h"
#include "components/rendering/rendering_engine.h"

// Initialize file-based config repository
nextgen::engine::configuration::FileLoader fileLoader("config.yaml");
nextgen::engine::configuration::ConfigRepository configRepo(fileLoader);

// Initialize rendering engine and other components
nextgen::engine::rendering::RenderingEngine renderingEngine;

// Set up orchestrator with configuration managers
nextgen::engine::configuration::ConfigOrchestrator orchestrator(configRepo, renderingEngine);

// Apply configurations in correct order
orchestrator.Configure();
```

### Summary

Configuration system follows a well-structured, modular, and extensible design that aligns with modern C++ best practices. By using templates, encapsulation, hierarchical management, and default handling, the system provides a flexible foundation for managing configurations across complex, interdependent components in a game engine. The addition of the ConfigOrchestrator enables controlled, centralized configuration application, essential for handling intricate component relationships, such as rendering API switching.
