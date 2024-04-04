load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "rendering_engine",
    srcs = [
        # Vulkan API
        "vulkan/vulkan_device_priority.c",
        "vulkan/vulkan_device_priority.h",
        "vulkan/vulkan_operations.c",
        "vulkan/vulkan_operations.h",
        "vulkan/vulkan_rendering.cc",
    ],
    hdrs = [
        "rendering.h",
        "vulkan/vulkan_config.h",
        "vulkan/vulkan_rendering.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//components/configuration:config_manager",
        "@libglfw",
        "@libvulkan",
    ],
)
