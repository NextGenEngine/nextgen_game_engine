load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_test")

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

cc_binary(
    name = "singleton_direct_access",
    srcs = [
        "singleton_direct_access.cc",
    ],
)

cc_binary(
    name = "engine_classes_sizes",
    srcs = [
        "engine_classes_sizes.cc",
    ],
    deps = [
        "//components/configuration:config_manager",
        "//components/engine:nextgen_game_engine",
        "//components/rendering:rendering_engine",
        "@google_benchmark//:benchmark_main",
    ],
)

cc_test(
    name = "raw_ref_versus_smart_pointers_test",
    srcs = [
        "raw_ref_versus_smart_pointers/raw_ref_versus_smart_pointers.h",
        "raw_ref_versus_smart_pointers/raw_ref_versus_smart_pointers_test.cc",
    ],
    deps = [
        "@googletest//:gtest_main",  # GoogleTest main entry point
    ],
)

# Target for the benchmarks
cc_binary(
    name = "raw_ref_versus_smart_pointers_benchmark",
    srcs = [
        "raw_ref_versus_smart_pointers/raw_ref_versus_smart_pointers.h",
        "raw_ref_versus_smart_pointers/raw_ref_versus_smart_pointers_benchmark.cc",
    ],
    deps = [
        "@google_benchmark//:benchmark_main",  # Google Benchmark main entry point
    ],
)
