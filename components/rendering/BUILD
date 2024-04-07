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
        "vulkan/vulkan_device_priority.c",
        "vulkan/vulkan_device_priority.h",
        "vulkan/vulkan_operations.c",
        "vulkan/vulkan_operations.h",
        "vulkan/vulkan_rendering.cc",
        "vulkan/vulkan_rendering.h",
        "vulkan/vulkan_config.h",
    ],
    hdrs = [
        "rendering.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":rendering_api",
        "//components/configuration:config_manager",
        "@libglfw",
        "@libvulkan",
    ],
)
