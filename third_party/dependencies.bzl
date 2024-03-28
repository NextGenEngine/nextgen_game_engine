# third_party/dependencies.bzl
"""third_party dependencies"""

def define_system_dependencies(name):
    native.new_local_repository(
        name = "libglfw",
        build_file = "@//third_party/glfw:BUILD",
        path = "/usr",
    )
    native.new_local_repository(
        name = "libvulkan",
        build_file = "@//third_party/vulkan:BUILD",
        path = "/usr",
    )
