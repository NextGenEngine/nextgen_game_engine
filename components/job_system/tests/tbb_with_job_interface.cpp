#include <tbb/parallel_for_each.h>

#include <chrono>
#include <iostream>
#include <memory>
#include <vector>

#include "../src/job.h"
#include "tests_constants.h"

class PrintJob : public Job {
  int id{};

 public:
  PrintJob() = default;

  // NOLINTNEXTLINE(readability-identifier-length)
  explicit PrintJob(int id) : id(id) {}

  inline void execute() override {
    if (id % PRINT_EVERY_NUMBER == 0) {
      std::cout << "i am " << id << "th job\n";
    }
  }
};

// NOLINTNEXTLINE(*avoid-c-arrays)
PrintJob jobs[NUMBER_OF_TEST_JOBS];  // Static array of Job pointers

int main() {
  // Start timer
  auto start_full = std::chrono::high_resolution_clock::now();
  // Allocate and initialize jobs
  for (int i = 0; i < NUMBER_OF_TEST_JOBS; ++i) {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
    jobs[i] = PrintJob(i + 1);
  }

  // Start timer
  auto start = std::chrono::high_resolution_clock::now();

  // Execute the jobs in parallel
  tbb::parallel_for(0, NUMBER_OF_TEST_JOBS,
                    [](int index) { jobs[index].execute(); });

  // Stop timer
  auto end = std::chrono::high_resolution_clock::now();

  // Calculate elapsed time
  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();

  std::cout << "parallel_for execution took " << duration << " milliseconds.\n";

  // Clean up
  // for (int i = 0; i < NUMBER_OF_TEST_JOBS; ++i)
  // {
  //     delete jobs[i]; // Manually delete allocated jobs
  // }

  // Stop timer
  auto end_full = std::chrono::high_resolution_clock::now();

  // Calculate elapsed time
  auto duration_full = std::chrono::duration_cast<std::chrono::milliseconds>(
                           end_full - start_full)
                           .count();

  std::cout << "Full Execution took " << duration_full << " milliseconds.\n";

  return 0;
}
