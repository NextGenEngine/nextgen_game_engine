load("@rules_cc//cc:defs.bzl", "cc_import")

cc_import(
    name = "libvulkan",
    hdrs = glob([
        "include/vulkan/**/*.h",
        "include/vk_video/**/*.h",
    ]),
    includes = ["include"],
    shared_library = "lib/x86_64-linux-gnu/libvulkan.so",
    visibility = ["//visibility:public"],
)
