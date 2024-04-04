load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "nextgen_game_engine",
    srcs = [
        "nextgen_game_engine.cc",
        "nextgen_game_engine.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//components/configuration:config_manager",
        "//components/rendering:rendering_engine",
    ],
)
