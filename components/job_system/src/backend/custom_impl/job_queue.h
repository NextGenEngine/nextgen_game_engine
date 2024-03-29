#ifndef JOB_QUEUE_H
#define JOB_QUEUE_H

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>

using Job = std::function<void()>;

class JobQueue {
 public:
  void addJob(const Job &job);
  Job getNextJob();

 private:
  std::queue<Job> queue;
  std::mutex mutex;
  std::condition_variable cv;
};

#endif  // JOB_QUEUE_H
