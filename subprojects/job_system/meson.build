project('green_threads_job_system', 'cpp', default_options: ['cpp_std=c++20'])

hwloc_dep = dependency('hwloc')
boost_dep = dependency('boost', modules: ['thread', 'fiber', 'context'])
onetbb_dep = dependency('tbb')

executable(
    'custom_impl',
    sources: [
        'tests/custom_impl.cpp',
        'src/backend/custom_impl/core_detector.cpp',
        'src/backend/custom_impl/thread_pool_manager.cpp',
        'src/backend/custom_impl/thread_worker.cpp',
        'src/backend/custom_impl/job_queue.cpp',
        'src/backend/custom_impl/job_manager.cpp',
    ],
    dependencies: [hwloc_dep, boost_dep],
)

executable(
    'pure_tbb',
    sources: [
        'tests/pure_tbb.cpp',
    ],
    dependencies: [onetbb_dep],
)

executable(
    'tbb_with_job_interface',
    sources: [
        'tests/tbb_with_job_interface.cpp',
    ],
    dependencies: [onetbb_dep],
)

executable(
    'pure_fibers',
    sources: [
        'tests/pure_fibers.cpp',
    ],
    dependencies: [boost_dep],
)
