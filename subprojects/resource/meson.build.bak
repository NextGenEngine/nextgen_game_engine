# meson.build - Meson build system configuration for the Resource Management module

project('resource_management', 'rust',
  version : '0.1.0',
  default_options : ['warning_level=3'])

# Define the main library target
lib_resource_management = static_library('resource_management',
  sources : [
    'lib.rs',
    'asset_loader.rs',
    'asset_cache.rs',
    'asset_handle.rs',
    'hot_reloader.rs',
  ],
  rust_args : ['--crate-type=lib'],
)

# Additional build configurations and dependencies will go here