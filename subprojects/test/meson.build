project(
    'nextgen_game_engine_test',
    'rust',
    version: '0.1',
    default_options: ['warning_level=3', 'buildtype=release', 'strip=true'],
)

engine_lib = dependency('nextgen_engine_static_dep', required: true)

executable(
    'nextgen_game_engine_test',
    sources: [
        'src/main.rs',
    ],
    dependencies: [engine_lib],
)
