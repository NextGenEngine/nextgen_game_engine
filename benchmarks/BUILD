load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "benchmarks_move_semantic",
    srcs = [
        "config_manager_move.h",
        "move_semantic_versus_references.cc",
    ],
    deps = [
        "//components/configuration:config_manager",
        "@google_benchmark//:benchmark_main",
    ],
)

cc_binary(
    name = "templated_structure_accessor",
    srcs = [
        "templated_structure_accessor.cc",
    ],
)
