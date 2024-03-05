project('game_world_management', 'rust')

world_manager_subdir = include_directories('src/world_manager')
scene_subdir = include_directories('src/scene')
ecs_subdir = include_directories('src/ecs')
spatial_partitioning_subdir = include_directories('src/spatial_partitioning')
level_streaming_subdir = include_directories('src/level_streaming')
persistence_subdir = include_directories('src/persistence')

executable('game_world_management',
  sources: [
    'src/main.rs',
    'src/world_manager/mod.rs',
    'src/scene/mod.rs',
    'src/ecs/mod.rs',
    'src/spatial_partitioning/mod.rs',
    'src/level_streaming/mod.rs',
    'src/persistence/mod.rs',
  ],
  include_directories: [
    world_manager_subdir,
    scene_subdir,
    ecs_subdir,
    spatial_partitioning_subdir,
    level_streaming_subdir,
    persistence_subdir,
  ],
  rust_args: ['--edition=2018'],
)