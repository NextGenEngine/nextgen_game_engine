load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "rendering_engine_vulkan",
    srcs = [
        "vulkan_operations.c",
    ],
    hdrs = [
        "vulkan_operations.h",
    ],
    copts = [
        "-isystemexternal/libvulkan/include",
        "-isystemexternal/libvulkan/include/x86_64-linux-gnu",
        "-isystemexternal/libglfw/include",
        "-isystemexternal/libglfw/include/x86_64-linux-gnu",
    ],  # Use -isystem to add system headers
    linkopts = [
        # "-L/usr/lib/x86_64-linux-gnu",  # Example path where GLFW and Vulkan might be installed
        "-Wl,-rpath-link,/usr/lib/x86_64-linux-gnu",  # Use rpath to specify runtime library search path
        "-Wl,-rpath-link,/lib64",  # Use rpath to specify runtime library search path
        # "-static", # This flag tells the linker to produce a fully static binary.
        "-static-libgcc",  # Static link libgcc
        "-static-libstdc++",  # Static link libstdc++
        # "-lglfw",
        # "-lvulkan",
        # other linker options as needed...
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//components/configuration:config_manager",
        "@libglfw",
        "@libvulkan",
    ],
)
