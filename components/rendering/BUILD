load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "rendering_api",
    hdrs = [
        "rendering_api.h",
    ],
    visibility = ["//visibility:private"],
    deps = [
        "@libglfw",
        "@libvulkan",
    ],
)

cc_library(
    name = "rendering_engine",
    srcs = [
        "rendering_engine_switch_api.cc",
        "rendering_engine.cc",
        "rendering_config.h",

        # Vulkan API
        "api/vulkan/vulkan_buffer.cc",
        "api/vulkan/vulkan_buffer.h",
        "api/vulkan/vulkan_command_buffers.cc",
        "api/vulkan/vulkan_command_buffers.h",
        "api/vulkan/vulkan_command_pool.cc",
        "api/vulkan/vulkan_command_pool.h",
        "api/vulkan/vulkan_config.h",
        "api/vulkan/vulkan_constants.h",
        "api/vulkan/vulkan_context.h",
        "api/vulkan/vulkan_depth_resources.cc",
        "api/vulkan/vulkan_depth_resources.h",
        "api/vulkan/vulkan_descriptor_set.cc",
        "api/vulkan/vulkan_descriptor_set.h",
        "api/vulkan/vulkan_descriptor_set_layout.cc",
        "api/vulkan/vulkan_descriptor_set_layout.h",
        "api/vulkan/vulkan_device_priority.c",
        "api/vulkan/vulkan_device_priority.h",
        "api/vulkan/vulkan_device.cc",
        "api/vulkan/vulkan_device.hh",
        "api/vulkan/vulkan_descriptor_pool.cc",
        "api/vulkan/vulkan_descriptor_pool.h",
        "api/vulkan/vulkan_frame_buffers.cc",
        "api/vulkan/vulkan_frame_buffers.h",
        "api/vulkan/vulkan_index_buffer.cc",
        "api/vulkan/vulkan_index_buffer.h",
        "api/vulkan/vulkan_instance.cc",
        "api/vulkan/vulkan_instance.h",
        "api/vulkan/vulkan_model_loader.cc",
        "api/vulkan/vulkan_model_loader.h",
        "api/vulkan/vulkan_pipeline.cc",
        "api/vulkan/vulkan_pipeline.h",
        "api/vulkan/vulkan_render_pass.cc",
        "api/vulkan/vulkan_render_pass.h",
        "api/vulkan/vulkan_rendering.cc",
        "api/vulkan/vulkan_rendering.h",
        "api/vulkan/vulkan_swapchain.cc",
        "api/vulkan/vulkan_swapchain.h",
        "api/vulkan/vulkan_swapchain_types.h",
        "api/vulkan/vulkan_sync_object.cc",
        "api/vulkan/vulkan_sync_object.h",
        "api/vulkan/vulkan_texture_image.cc",
        "api/vulkan/vulkan_texture_image.h",
        "api/vulkan/vulkan_types.h",
        "api/vulkan/vulkan_uniform_buffer.cc",
        "api/vulkan/vulkan_uniform_buffer.h",
        "api/vulkan/vulkan_validation_layers.cc",
        "api/vulkan/vulkan_validation_layers.h",
        "api/vulkan/vulkan_vertex_buffer.cc",
        "api/vulkan/vulkan_vertex_buffer.h",
        "api/vulkan/window_surface.h",
    ],
    hdrs = [
        "rendering_engine.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":rendering_api",
        "//components/configuration:config_repo",
        "//components/engine:nextgen_game_engine_types",
        "//lib:std_ext",
        "//third_party/stb",
        "@glm",
        "@libglfw",
        "@libvulkan",
        "@tinyobjloader",
    ],
)
