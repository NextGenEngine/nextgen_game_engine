project('green_threads_job_system', 'cpp', default_options: ['cpp_std=c++20'])

hwloc_dep = dependency('hwloc')
boost_dep = dependency('boost', modules: ['thread', 'fiber'])

executable(
    'green_threads_job_system',
    sources: [
        'main.cpp',
        'core_detector.cpp',
        'thread_pool_manager.cpp',
        'thread_worker.cpp',
        'job_queue.cpp',
        'job_manager.cpp',
    ],
    dependencies: [hwloc_dep, boost_dep],
    install: true,
)
