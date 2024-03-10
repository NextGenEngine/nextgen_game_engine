project('green_threads_job_system', 'cpp', default_options: ['cpp_std=c++20'])

hwloc_dep = dependency('hwloc')
boost_dep = dependency('boost', modules: ['thread', 'fiber', 'context'])
onetbb_dep = dependency('tbb')

# Sources
test_custom_impl_sources = [
    'tests/custom_impl.cpp',
    'src/backend/custom_impl/core_detector.cpp',
    'src/backend/custom_impl/thread_pool_manager.cpp',
    'src/backend/custom_impl/thread_worker.cpp',
    'src/backend/custom_impl/job_queue.cpp',
    'src/backend/custom_impl/job_manager.cpp',
]

executable(
    'custom_impl',
    sources: test_custom_impl_sources,
    dependencies: [hwloc_dep, boost_dep],
)

test_pure_tbb_sources = [
    'tests/pure_tbb.cpp',
]

executable(
    'pure_tbb',
    sources: test_pure_tbb_sources,
    dependencies: [onetbb_dep],
)

test_tbb_with_job_interface_sources = [
    'tests/tbb_with_job_interface.cpp',
]

executable(
    'tbb_with_job_interface',
    sources: test_tbb_with_job_interface_sources,
    dependencies: [onetbb_dep],
)

test_pure_fibers_sources = [
    'tests/pure_fibers.cpp',
]
executable(
    'pure_fibers',
    sources: test_pure_fibers_sources,
    dependencies: [boost_dep],
)

all_source_files = (
    test_custom_impl_sources + test_pure_tbb_sources + test_tbb_with_job_interface_sources + test_pure_fibers_sources
)

# Define a run target for formatting
run_target(
    'format-code',
    command: ['clang-format', '-i', files(all_source_files)],
    depends: [],
)
