#ifndef JOB_MANAGER_H
#define JOB_MANAGER_H

#include "job_queue.h"

class JobManager {
 public:
  JobManager(JobQueue &jobQueue);
  void addJob(const Job &job);

 private:
  JobQueue &jobQueue;
};

#endif  // JOB_MANAGER_H
