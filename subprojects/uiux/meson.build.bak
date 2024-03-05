project('ui_ux_system', 'rust')

ui_ux_deps = dependency('rust', version : '>=1.0')

ui_ux_lib = static_library('ui_ux_system', 'ui_ux_system/mod.rs',
    dependencies : ui_ux_deps,
    install : true
)

executable('game_engine', 'main.rs',
    link_with : ui_ux_lib,
    install : true
)