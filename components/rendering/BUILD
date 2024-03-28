load("@rules_cc//cc:defs.bzl", "cc_binary")

# cc_library(
#     name = "config_loader",
#     hdrs = ["config_loader.h"],
#     visibility = ["//visibility:private"],
# )

cc_binary(
    name = "rendering_engine",
    srcs = [
        "rendering.cc",
    ],
    # copts = [
    #     "-isystemexternal/libvulkan/include",
    #     "-isystemexternal/libvulkan/include/x86_64-linux-gnu",
    #     "-isystemexternal/libglfw/include",
    #     "-isystemexternal/libglfw/include/x86_64-linux-gnu",
    # ],  # Use -isystem to add system headers
    linkopts = [
        # "-L/usr/lib/x86_64-linux-gnu",  # Example path where GLFW and Vulkan might be installed
        "-ldl",
        "-Wl,-rpath-link,/usr/lib/x86_64-linux-gnu",  # Use rpath to specify runtime library search path
        "-Wl,-rpath-link,/lib64",  # Use rpath to specify runtime library search path
        "-static-libgcc",  # Static link libgcc
        "-static-libstdc++",  # Static link libstdc++
        # "-lglfw",
        # "-lvulkan",
        # other linker options as needed...
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//components/configuration:config_manager",
        "//components/rendering/vulkan:rendering_engine_vulkan",
    ],
)
