load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "rendering_engine",
    srcs = [
        "rendering.cc",
        "rendering.h",
        # Vulkan API
        "vulkan/vulkan_device_priority.c",
        "vulkan/vulkan_device_priority.h",
        "vulkan/vulkan_operations.c",
        "vulkan/vulkan_operations.h",
        "vulkan/vulkan_rendering.cc",
        "vulkan/vulkan_rendering.h",
        "vulkan/vulkan_config.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//components/configuration:config_manager",
        "@libglfw",
        "@libvulkan",
    ],
)
