# Benchmarks

## Comparing performance of move semantics versus references

Measuring performance of identical classes by functionality,
but using different constructor definitions.

One is using pass-by-const-reference, another is using move semantics
modern language feature.

Results:

| Benchmark                                 | Time    | CPU     | Iterations |
| ----------------------------------------- | ------- | ------- | ---------- |
| BM_CONFIG_MANAGER_REF/iterations:1000000  | 4.19 us | 4.19 us | 1000000    |
| BM_CONFIG_MANAGER_REF/iterations:1000000  | 3.16 us | 3.16 us | 1000000    |
| BM_CONFIG_MANAGER_MOVE/iterations:1000000 | 3.00 us | 3.00 us | 1000000    |
| BM_CONFIG_MANAGER_MOVE/iterations:1000000 | 2.91 us | 2.91 us | 1000000    |

Reordering:

| Benchmark                                 | Time    | CPU     | Iterations |
| ----------------------------------------- | ------- | ------- | ---------- |
| BM_CONFIG_MANAGER_MOVE/iterations:1000000 | 4.05 us | 4.05 us | 1000000    |
| BM_CONFIG_MANAGER_MOVE/iterations:1000000 | 3.26 us | 3.26 us | 1000000    |
| BM_CONFIG_MANAGER_REF/iterations:1000000  | 2.97 us | 2.97 us | 1000000    |
| BM_CONFIG_MANAGER_REF/iterations:1000000  | 2.89 us | 2.89 us | 1000000    |

There is no difference. Difference you see is about the order tests are running.
In first case "references" are running first and are a bit slower (especially
first warmup loop). In second test "move semantic" goes first and the same
a bit slower.

BTW in previous commit (check history) I made a mistake. And "move semantic"
was showing 1.5x boost in performance, but it was related only to the fact,
that "reference" was using additional inline function call (and clang compiler
did not inlined this function for some reason), but "move semantic" was running
same code, but without function. That give 1.5x faster execution. Now it is
a question for me: how to ensure compiler inlines this function call.

## Compare class sizes when using ComponentConfig as direct member vs pointer

**Direct member:**
nextgen::engine::configuration::ConfigManager: 80
nextgen::engine::configuration::ComponentConfig: 72
nextgen::engine::rendering::RenderingEngineConfig: 4
nextgen::engine::rendering::RenderingConfigurationStrategySelector: 264
nextgen::engine::rendering::RenderingAPIEnum: 4
nextgen::engine::rendering::RenderingConfigurationPrimaryStrategyData: 88
nextgen::engine::rendering::RenderingConfigurationPrimaryStrategy: 96
nextgen::engine::rendering::RenderingConfigurationDefaultStrategyData: 88
nextgen::engine::rendering::RenderingConfigurationDefaultStrategy: 96
nextgen::engine::rendering::RenderingConfigurationStrategy: 464
nextgen::engine::rendering::RenderingConfigValidator: 1
nextgen::engine::rendering::vulkan::VulkanConfig: 16
nextgen::engine::rendering::vulkan::VulkanConfigurationPrimaryStrategyData: 80
nextgen::engine::rendering::vulkan::VulkanConfigurationPrimaryStrategy: 88
nextgen::engine::rendering::vulkan::VulkanConfigurationDefaultStrategyData: 80
nextgen::engine::rendering::vulkan::VulkanConfigurationDefaultStrategy: 88
nextgen::engine::rendering::vulkan::VulkanConfigStrategy: 184
nextgen::engine::rendering::vulkan::VulkanInstance: 8
nextgen::engine::rendering::vulkan::VulkanContext: 56
nextgen::engine::rendering::vulkan::VulkanDevice: 16
nextgen::engine::rendering::vulkan::VulkanSwapChain: 8
nextgen::engine::rendering::vulkan::VulkanRenderingApi: 192
nextgen::engine::rendering::RenderingEngineData: 208
nextgen::engine::rendering::RenderingEngine: 216
nextgen::engine::NextGenEngine: 752

**Pointer, where possible:**
nextgen::engine::configuration::ConfigManager: 80
nextgen::engine::configuration::ComponentConfig: 72
nextgen::engine::rendering::RenderingEngineConfig: 4
nextgen::engine::rendering::RenderingConfigurationStrategySelector: 208
nextgen::engine::rendering::RenderingAPIEnum: 4
nextgen::engine::rendering::RenderingConfigurationPrimaryStrategyData: 24
nextgen::engine::rendering::RenderingConfigurationPrimaryStrategy: 32
nextgen::engine::rendering::RenderingConfigurationDefaultStrategyData: 24
nextgen::engine::rendering::RenderingConfigurationDefaultStrategy: 32
nextgen::engine::rendering::RenderingConfigurationStrategy: 352
nextgen::engine::rendering::RenderingConfigValidator: 1
nextgen::engine::rendering::vulkan::VulkanConfig: 16
nextgen::engine::rendering::vulkan::VulkanConfigurationPrimaryStrategyData: 16
nextgen::engine::rendering::vulkan::VulkanConfigurationPrimaryStrategy: 24
nextgen::engine::rendering::vulkan::VulkanConfigurationDefaultStrategyData: 16
nextgen::engine::rendering::vulkan::VulkanConfigurationDefaultStrategy: 24
nextgen::engine::rendering::vulkan::VulkanConfigStrategy: 128
nextgen::engine::rendering::vulkan::VulkanInstance: 8
nextgen::engine::rendering::vulkan::VulkanContext: 56
nextgen::engine::rendering::vulkan::VulkanDevice: 16
nextgen::engine::rendering::vulkan::VulkanSwapChain: 8
nextgen::engine::rendering::vulkan::VulkanRenderingApi: 192
nextgen::engine::rendering::RenderingEngineData: 208
nextgen::engine::rendering::RenderingEngine: 216
nextgen::engine::NextGenEngine: 640

It seems `ComponentConfig` takes a log of space, because of YAML::Node direct member. Using `ComponentConfig`
as pointer, and storing only one copy for each component, decreases class/struct sizes for ~100 bytes.
And final size of engine is 640 bytes vs 752 bytes, when used as direct member.
It is maybe not so great result, assuming that `ComponentConfig` itself takes 72 bytes, and I have replaces
4 places, where it is used. So you can think why its decrease only for 100 bytes, but not for 200, for example?
It is because `ComponentConfig` was used in two components, meaning that after refactoring and start using
pointers instead of direct members, I still need to have 2 copies of `ComponentConfig` - one for each of component.
And also I need now 4 pointers (8 byte for each of the pointer - 32 bytes in total). Thats why result is not so great.
So here it is more a question about cache locality - how this will affect it.
It is very good example of why it make sense to use direct members instead of pointers, when you code
is well designed, even when objects are quite big (about 100 bytes), This is happening, because in good design
we avoid repetitions and use Single Responsibility principle, so these big objects usually belong to only one instance
of only one class in the system. Less use of pointers makes code execute faster and better suits with cache
locality.

There is still room for improvements.
