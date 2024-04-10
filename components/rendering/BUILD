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
        "rendering.cc",
        "rendering_config.h",
        # Vulkan API
        "vulkan/vulkan_buffer.h",
        "vulkan/vulkan_command_pool.h",
        "vulkan/vulkan_config.h",
        "vulkan/vulkan_context.h",
        "vulkan/vulkan_device_priority.c",
        "vulkan/vulkan_device_priority.h",
        "vulkan/vulkan_device.cc",
        "vulkan/vulkan_device.hh",
        "vulkan/vulkan_frame_buffers.h",
        "vulkan/vulkan_instance.cc",
        "vulkan/vulkan_instance.h",
        "vulkan/vulkan_pipeline.h",
        "vulkan/vulkan_render_pass.h",
        "vulkan/vulkan_rendering.cc",
        "vulkan/vulkan_rendering.h",
        "vulkan/vulkan_shader.h",
        "vulkan/vulkan_swapchain.cc",
        "vulkan/vulkan_swapchain.h",
        "vulkan/window_surface.h",
    ],
    hdrs = [
        "rendering.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":rendering_api",
        "//components/configuration:config_manager",
        "//lib:std_ext",
        "@libglfw",
        "@libvulkan",
    ],
)
