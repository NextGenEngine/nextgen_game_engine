project('nextgen_game_engine', 'rust', 'c',
  version : '0.1',
  default_options : ['warning_level=3', 'buildtype=release',
  'strip=true'])

vulkan_dep = dependency('vulkan', required : true)
glfw_dep = dependency('glfw3', required : true)

vulkan_operations_lib = static_library('vulkan_operations',
  'lib/vulkan_impl/vulkan_operations.c',
  dependencies : [vulkan_dep, glfw_dep])

# executable('vulkan_operations_test',
#   'vulkan_operations_test.c',
#   link_with : vulkan_operations_lib,
#   dependencies : vulkan_dep)

executable('nextgen_game_engine',
    sources : ['src/main.rs',
    'src/game_mechanics.rs', 'src/graphics_abstractor.rs',
    'src/input_management.rs', 'src/rendering.rs',
    'src/scene_management.rs', 'src/timeline_management.rs',
    'src/vulkan_api.rs'],
    link_with : [vulkan_operations_lib],
    install : true)
