load("@rules_cc//cc:defs.bzl", "cc_import")

cc_import(
    name = "libvulkan",
    shared_library = select({
        "@platforms//os:linux": "lib/x86_64-linux-gnu/libvulkan.so",
        "@platforms//os:macos": "lib/x86_64-macos/libvulkan.dylib",
        "@platforms//os:windows": "lib/x86_64-windows-gnu/vulkan.dll",
        "//conditions:default": None,
    }),
    visibility = ["//visibility:public"],
)
