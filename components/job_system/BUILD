load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "job_system",
    srcs = [
        "backend/custom_impl/core_detector.cpp",
        "backend/custom_impl/core_detector.h",
        "backend/custom_impl/job_manager.cpp",
        "backend/custom_impl/job_manager.h",
        "backend/custom_impl/job_queue.cpp",
        "backend/custom_impl/job_queue.h",
        "backend/custom_impl/thread_pool_manager.cpp",
        "backend/custom_impl/thread_pool_manager.h",
        "backend/custom_impl/thread_worker.cpp",
        "backend/custom_impl/thread_worker.h",
    ],
    visibility = ["//visibility:public"],
)
