load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "rendering_engine_vulkan",
    srcs = [
        "vulkan_device_priority.c",
        "vulkan_device_priority.h",
        "vulkan_operations.c",
    ],
    hdrs = [
        "vulkan_operations.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//components/configuration:config_manager",
        "@libglfw",
        "@libvulkan",
    ],
)
