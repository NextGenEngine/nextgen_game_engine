workspace(name = "nextgen_game_engine")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# Third party dependencies installed in system (Vulkan, GLFW, etc)
load("//third_party:dependencies.bzl", "define_system_dependencies")

http_archive(
    name = "glm",
    build_file = "//third_party/glm:BUILD",  # Reference your custom BUILD file
    strip_prefix = "glm-0.9.9.8",
    urls = ["https://github.com/g-truc/glm/archive/refs/tags/0.9.9.8.tar.gz"],
)

define_system_dependencies("")
