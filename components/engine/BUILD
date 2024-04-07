load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "nextgen_game_engine",
    srcs = [
        "nextgen_game_engine.cc",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//components/configuration:config_manager",
        "//components/rendering:rendering_engine",
    ],
)
