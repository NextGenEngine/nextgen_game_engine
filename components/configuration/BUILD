load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "config_manager",
    srcs = [
        "config_loader.cc",
        "config_manager.cc",
    ],
    hdrs = [
        "config_loader.h",
        "config_manager.h",
    ],
    visibility = ["//visibility:public"],
    deps = ["@yaml-cpp//:yaml-cpp"],
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
