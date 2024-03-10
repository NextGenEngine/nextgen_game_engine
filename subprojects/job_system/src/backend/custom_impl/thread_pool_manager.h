#ifndef THREAD_POOL_MANAGER_H
#define THREAD_POOL_MANAGER_H

#include <thread>
#include <vector>

#include "job_queue.h"
#include "thread_worker.h"

class ThreadPoolManager {
 public:
  ThreadPoolManager(int numCores, JobQueue &jobQueue);
  ~ThreadPoolManager();

  void initialize();
  void start();
  void join();
  void terminate();

 private:
  int numCores;
  JobQueue &jobQueue;
  std::vector<std::unique_ptr<ThreadWorker>> workers;
  std::vector<std::thread> workerThreads;
};

#endif  // THREAD_POOL_MANAGER_H
