load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "rendering_api",
    hdrs = [
        "rendering_api.h",
    ],
    visibility = ["//visibility:private"],
    deps = [
        "@libglfw",
        "@libvulkan",
    ],
)

cc_library(
    name = "rendering_engine",
    srcs = [
        "config_strategy/rendering_config_strategy.h",
        "config_strategy/rendering_config_strategy.cc",
        "config_strategy/rendering_config_strategy_default.h",
        "config_strategy/rendering_config_strategy_default.cc",
        "config_strategy/rendering_config_strategy_primary.h",
        "config_strategy/rendering_config_strategy_primary.cc",
        "config_strategy/rendering_config_sub_strategy_selector.h",
        "config_strategy/rendering_config_sub_strategy_selector.cc",
        "config_strategy/rendering_config_validator.h",
        "config_strategy/rendering_config_validator.cc",
        "rendering.cc",
        "rendering_config.h",

        # Vulkan API
        "api/vulkan/config_strategy/vulkan_config_strategy.h",
        "api/vulkan/config_strategy/vulkan_config_strategy.cc",
        "api/vulkan/config_strategy/vulkan_config_strategy_default.cc",
        "api/vulkan/config_strategy/vulkan_config_strategy_default.h",
        "api/vulkan/config_strategy/vulkan_config_strategy_primary.cc",
        "api/vulkan/config_strategy/vulkan_config_strategy_primary.h",
        "api/vulkan/config_strategy/vulkan_config_validator.cc",
        "api/vulkan/config_strategy/vulkan_config_validator.h",
        "api/vulkan/vulkan_buffer.h",
        "api/vulkan/vulkan_command_pool.h",
        "api/vulkan/vulkan_config.h",
        "api/vulkan/vulkan_context.h",
        "api/vulkan/vulkan_device_priority.c",
        "api/vulkan/vulkan_device_priority.h",
        "api/vulkan/vulkan_device.cc",
        "api/vulkan/vulkan_device.hh",
        "api/vulkan/vulkan_frame_buffers.h",
        "api/vulkan/vulkan_instance.cc",
        "api/vulkan/vulkan_instance.h",
        "api/vulkan/vulkan_pipeline.h",
        "api/vulkan/vulkan_render_pass.h",
        "api/vulkan/vulkan_rendering.cc",
        "api/vulkan/vulkan_rendering.h",
        "api/vulkan/vulkan_shader.h",
        "api/vulkan/vulkan_swapchain.cc",
        "api/vulkan/vulkan_swapchain.h",
        "api/vulkan/window_surface.h",
        "api/vulkan/vulkan_validation_layers.cc",
        "api/vulkan/vulkan_validation_layers.h",

        # DIRECTX API
        "api/directx/directx_config_strategy.h",
    ],
    hdrs = [
        "config_strategy/rendering_config_strategy.h",
        "rendering.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":rendering_api",
        "//components/configuration:config_manager",
        "//components/engine:nextgen_game_engine_types",
        "//lib:std_ext",
        "@libglfw",
        "@libvulkan",
    ],
)
