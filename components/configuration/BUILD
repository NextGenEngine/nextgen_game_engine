load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

cc_library(
    name = "config_repo",
    srcs = [
        "repository/config_loader.cc",
        "repository/config_repo.cc",
    ],
    hdrs = [
        "managers/config_manager_template.h",
        "repository/config_loader.h",
        "repository/config_repo.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//lib:std_ext",
        "@yaml-cpp//:yaml-cpp",
    ],
)

cc_library(
    name = "config_orchestrator",
    srcs = [
        "managers/rendering_engine_config_manager.h",
        "managers/vulkan_rendering_api_config_manager.h",
        "orchestrator/config_orchestrator.cc",
    ],
    hdrs = [
        "orchestrator/config_orchestrator.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":config_repo",
        "//components/rendering:rendering_engine",
        "@yaml-cpp//:yaml-cpp",
    ],
)

cc_test(
    name = "config_system_test",
    size = "small",
    srcs = [
        "tests/config_manager_test.cc",
        "tests/config_repo_test.cc",
    ],
    deps = [
        ":config_orchestrator",
        ":config_repo",
        "//components/rendering:rendering_engine",
        "@googletest//:gtest_main",
    ],
)

cc_binary(
    name = "config_manager_benchmark",
    srcs = ["config_manager_benchmark.cc"],
    deps = [
        ":config_repo",
        "@google_benchmark//:benchmark_main",
    ],
)
