load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "config_loader",
    hdrs = ["config_loader.h"],
    visibility = ["//visibility:private"],
)

cc_library(
    name = "config_manager",
    srcs = [
        "config_manager.cc",
    ],
    hdrs = [
        "config_manager.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":config_loader",
        "@yaml-cpp//:yaml-cpp",
    ],
)

cc_test(
    name = "config_manager_test",
    size = "small",
    srcs = ["config_manager_test.cc"],
    deps = [
        ":config_manager",
        "@googletest//:gtest_main",
    ],
)
