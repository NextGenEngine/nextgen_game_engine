project(
    'nextgen_engine',
    'rust',
    version: '0.1',
    default_options: ['default_library=both'],
)

configuration_lib = dependency('nextgen_engine_configuration_static_dep', required: true)

deps = [configuration_lib]
configuration_dyn_lib = dependency('nextgen_engine_configuration_dyn_dep', required: true)

# Implementation crate
sources = files('src/engine.rs')
lib_static = static_library(
    'nextgen_engine',
    sources,
    dependencies: deps,
    rust_crate_type: 'rlib',
)

lib_dynamic = shared_library(
    'nextgen_engine',
    sources,
    dependencies: [configuration_dyn_lib],
    rust_crate_type: 'cdylib',
)

# Combine API and implementation into a single dependency
combined_dep_static = declare_dependency(
    link_with: lib_static,
    dependencies: deps,
)
combined_dep_dynamic = declare_dependency(link_with: lib_dynamic)

# Expose the combined dependency for consumers
set_variable('nextgen_engine_static_dep', combined_dep_static)
meson.override_dependency('nextgen_engine_static_dep', combined_dep_static)
set_variable('nextgen_engine_dyn_dep', combined_dep_dynamic)
meson.override_dependency('nextgen_engine_dyn_dep', combined_dep_dynamic)
