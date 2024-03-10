#include "thread_worker.h"

ThreadWorker::ThreadWorker(int coreId, JobQueue &jobQueue)
	: coreId(coreId), jobQueue(jobQueue) {}

void ThreadWorker::run() {
	while (!terminated) {
		auto job = jobQueue.getNextJob();
		if (job) {
			job();
		}
	}
}

void ThreadWorker::terminate() {
	// TODO(low priority): figure out if std::memory_order_relaxed can be used
	// here/ It's not very important. This is called once during all application
	// runtime cycle.
	// terminated.store(true, std::memory_order_relaxed);
	terminated.store(true);
}
