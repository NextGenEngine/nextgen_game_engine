load("@rules_cc//cc:defs.bzl", "cc_import")

cc_import(
    name = "libglfw",
    shared_library = select({
        "@platforms//os:linux": "lib/x86_64-linux-gnu/libglfw.so",
        "@platforms//os:macos": "lib/x86_64-macos/libglfw.dylib",
        "@platforms//os:windows": "lib/x86_64-windows-gnu/libglfw.dll",
        "//conditions:default": None,
    }),
    visibility = ["//visibility:public"],
)
