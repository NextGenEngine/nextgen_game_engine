project('physics_engine', 'rust')

physics_engine_lib = static_library('physics_engine', 'src/lib.rs',
    rust_args : ['--crate-type=staticlib'])

executable('physics_engine_demo', 'src/main.rs',
    link_with : physics_engine_lib,
    install : true)