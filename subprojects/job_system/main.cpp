#include <job_manager.h>
#include <job_queue.h>
#include "core_detector.h"
#include <stdio.h>
#include <thread_pool_manager.h>
#include <iostream>
#include <future>

void terminateThreadPoolAfterDelay(ThreadPoolManager &threadPoolManager,
JobManager &jobManager)
{
    std::cout << "Running wait timer\n";
    std::this_thread::sleep_for(std::chrono::seconds(5)); // Sleep in async task
    std::cout << "Terminating thread pool manager (with its workers and jobs)\n";
    jobManager.addJob([&threadPoolManager]
                      { threadPoolManager.terminate(); });
}

int main()
{
    std::cout << "main ";

    CoreDetector coreDetector;
    int numCores = coreDetector.detectCores();

    std::cout << numCores;

    JobQueue jobQueue;
    ThreadPoolManager threadPoolManager(numCores, jobQueue);
    JobManager jobManager(jobQueue);

    std::cout << "JobManager";

    // Initialize the thread pool and bind threads to cores
    threadPoolManager.initialize();

    // Add jobs to the job queue
    for (int i = 0; i < 1000; ++i)
    {
        jobManager.addJob([i]
                          { std::cout << "i am " << i << " job\n"; });
    }

    auto future = std::async(
        std::launch::async,
        terminateThreadPoolAfterDelay,
        std::ref(threadPoolManager),
        std::ref(jobManager));
    future.wait();

    // Start the job processing
    threadPoolManager.start();

    // Wait for all jobs to complete
    threadPoolManager.join();

    return 0;
}
