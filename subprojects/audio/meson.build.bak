project('audio_engine', 'rust')

audio_engine_lib = static_library('audio_engine', 'src/lib.rs',
    dependencies : [],
    install : true
)

executable('audio_engine_demo', 'src/main.rs',
    dependencies : [audio_engine_lib],
    install : true
)