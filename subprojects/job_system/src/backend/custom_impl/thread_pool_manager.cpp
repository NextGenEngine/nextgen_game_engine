#include "thread_pool_manager.h"

#include <hwloc.h>

#include "thread_worker.h"

ThreadPoolManager::ThreadPoolManager(int numCores, JobQueue &jobQueue)
    : numCores(numCores), jobQueue(jobQueue) {}

ThreadPoolManager::~ThreadPoolManager() { join(); }

void ThreadPoolManager::initialize() {
  hwloc_topology_t topology = nullptr;
  hwloc_topology_init(&topology);
  hwloc_topology_load(topology);

  for (int i = 0; i < numCores; ++i) {
    hwloc_cpuset_t cpuset = hwloc_bitmap_alloc();
    hwloc_get_cpubind(topology, cpuset, HWLOC_CPUBIND_THREAD);
    hwloc_bitmap_only(cpuset, i);

    // workers.emplace_back([this, cpuset, i]()
    //                      {
    //                         hwloc_topology_t topology;
    //                             hwloc_topology_init(&topology);
    //                             hwloc_topology_load(topology);
    //     ThreadWorker worker(i, jobQueue);
    //     hwloc_set_cpubind(topology, cpuset, HWLOC_CPUBIND_THREAD);
    //     worker.run();
    //     hwloc_bitmap_free(cpuset); });

    workers.emplace_back(std::make_unique<ThreadWorker>(i, jobQueue));
    workerThreads.emplace_back([cpuset, &worker = workers.back()]() {
      hwloc_topology_t topology = nullptr;
      hwloc_topology_init(&topology);
      hwloc_topology_load(topology);
      hwloc_set_cpubind(topology, cpuset, HWLOC_CPUBIND_THREAD);
      worker->run();
      hwloc_bitmap_free(cpuset);
    });
  }

  hwloc_topology_destroy(topology);
}

void ThreadPoolManager::start() {
  // The threads are already running after initialization
}

void ThreadPoolManager::join() {
  for (auto &thread : workerThreads) {
    if (thread.joinable()) {
      thread.join();
    }
  }
}

void ThreadPoolManager::terminate() {
  for (auto &worker : workers) {
    worker->terminate();
  }
}
