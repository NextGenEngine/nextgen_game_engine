#include "job_queue.h"

void JobQueue::addJob(const Job &job)
{
    std::lock_guard<std::mutex> lock(mutex);
    queue.push(job);
    cv.notify_one();
}

Job JobQueue::getNextJob()
{
    std::unique_lock<std::mutex> lock(mutex);
    cv.wait(lock, [this]
            { return !queue.empty(); });
    Job job = queue.front();
    queue.pop();
    return job;
}
