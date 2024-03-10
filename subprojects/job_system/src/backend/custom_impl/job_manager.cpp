#include "job_manager.h"

JobManager::JobManager(JobQueue& jobQueue) : jobQueue(jobQueue) {}

void JobManager::addJob(const Job& job) {
    jobQueue.addJob(job);
}
