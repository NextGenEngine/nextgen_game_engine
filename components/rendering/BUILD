load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "rendering_engine",
    srcs = [
        "rendering.cc",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//components/configuration:config_manager",
        "//components/rendering/vulkan:rendering_engine_vulkan",
    ],
)
