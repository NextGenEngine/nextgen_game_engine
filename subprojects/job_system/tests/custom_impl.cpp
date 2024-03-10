#include <future>
#include <iostream>

#include "../src/backend/custom_impl/core_detector.h"
#include "../src/backend/custom_impl/job_manager.h"
#include "../src/backend/custom_impl/job_queue.h"
#include "../src/backend/custom_impl/thread_pool_manager.h"

void terminateThreadPoolAfterDelay(ThreadPoolManager &threadPoolManager,
								   JobManager &jobManager) {
	std::cout << "Running wait timer\n";
	std::this_thread::sleep_for(
		std::chrono::seconds(5));  // Sleep in async task
	std::cout
		<< "Terminating thread pool manager (with its workers and jobs)\n";
	jobManager.addJob([&threadPoolManager] { threadPoolManager.terminate(); });
}

int main() {
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
	for (int i = 0; i < 10000000; ++i) {
		jobManager.addJob([i]() {
			if (i % 1000000 == 0) {
				std::cout << "i am " << i << " job\n";
			}
		});
	}

	auto future = std::async(std::launch::async, terminateThreadPoolAfterDelay,
							 std::ref(threadPoolManager), std::ref(jobManager));
	future.wait();

	// Start the job processing
	threadPoolManager.start();

	// Wait for all jobs to complete
	threadPoolManager.join();

	return 0;
}
