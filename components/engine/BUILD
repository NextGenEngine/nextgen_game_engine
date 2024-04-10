load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
    name = "nextgen_game_engine",
    srcs = [
        "nextgen_game_engine.cc",
    ],
    hdrs = ["nextgen_game_engine.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//components/configuration:config_manager",
        "//components/rendering:rendering_engine",
        "@onetbb//:tbb",
    ],
)

cc_binary(
    name = "nextgen_game_engine_test",
    srcs = [
        "nextgen_game_engine_test.cc",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":nextgen_game_engine",
    ],
)
