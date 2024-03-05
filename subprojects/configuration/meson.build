project(
    'nextgen_engine_configuration',
    'rust',
    version: '0.1',
    default_options: ['default_library=both'],
)

# Implementation crate
sources = files('src/configuration.rs')
lib_static = static_library(
    'configuration',
    sources,
    rust_crate_type: 'rlib',
)

lib_dynamic = shared_library(
    'nextgen_engine_configuration_dyn',
    sources,
    rust_crate_type: 'cdylib',
)

# Combine API and implementation into a single dependency
combined_dep_static = declare_dependency(link_with: lib_static)
combined_dep_dynamic = declare_dependency(link_with: lib_dynamic)

# Expose the combined dependency for consumers
set_variable('nextgen_engine_configuration_static_dep', combined_dep_static)
meson.override_dependency('nextgen_engine_configuration_static_dep', combined_dep_static)
set_variable('nextgen_engine_configuration_dyn_dep', combined_dep_dynamic)
meson.override_dependency('nextgen_engine_configuration_dyn_dep', combined_dep_dynamic)

