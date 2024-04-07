load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

cc_library(
    name = "config_manager",
    srcs = ["config_manager_globals.cc"],
    hdrs = [
        "config_loader.h",
        "config_manager.h",
        "config_manager_globals.cc",
        "config_manager_globals.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
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

cc_binary(
    name = "config_manager_benchmark",
    srcs = ["config_manager_benchmark.cc"],
    deps = [
        ":config_manager",
        "@google_benchmark//:benchmark_main",
    ],
)
