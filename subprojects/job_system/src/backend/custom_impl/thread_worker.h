#ifndef THREAD_WORKER_H
#define THREAD_WORKER_H

#include <atomic>
#include "job_queue.h"

class ThreadWorker {
public:
    ThreadWorker(int coreId, JobQueue& jobQueue);
    void run();
    void terminate();

private:
    int coreId;
    JobQueue& jobQueue;
    std::atomic<bool> terminated{false};
};

#endif // THREAD_WORKER_H