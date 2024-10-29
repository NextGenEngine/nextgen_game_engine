load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
    name = "nextgen_game_engine_types",
    hdrs = [
        "nextgen_game_engine_interfaces.h",
        "nextgen_game_engine_results.h",
        "nextgen_game_engine_templates.h",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "nextgen_game_engine",
    srcs = [
        "nextgen_game_engine.cc",
    ],
    hdrs = [
        "nextgen_game_engine.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":nextgen_game_engine_types",
        "//components/configuration:config_orchestrator",
        "//components/configuration:config_repo",
        "//components/rendering:rendering_engine",
        "@onetbb//:tbb",
    ],
)

cc_binary(
    name = "nextgen_game_engine_test",
    srcs = [
        "nextgen_game_engine_test.cc",
    ],
    data = glob(["data/**"]),  # Include all files in the data directory
    visibility = ["//visibility:public"],
    deps = [
        ":nextgen_game_engine",
    ],
)
