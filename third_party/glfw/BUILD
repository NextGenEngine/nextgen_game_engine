load("@rules_cc//cc:defs.bzl", "cc_import")

# cc_library(
#     name = "glfw",
#     hdrs = glob([
#         "GLFW/**/*.h",
#         "GL/**/*.h",
#     ]),
#     linkopts = ["-lglfw", "-lX11"],  # Link against the GLFW library
#     visibility = ["//visibility:public"],
# )

cc_import(
    name = "libglfw",
    hdrs = glob(["include/**/*.h"]),
    includes = ["include"],
    shared_library = "lib/x86_64-linux-gnu/libglfw.so",
    visibility = ["//visibility:public"],
)
