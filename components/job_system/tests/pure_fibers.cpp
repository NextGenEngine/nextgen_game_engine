#include <boost/fiber/all.hpp>
#include <chrono>
#include <iostream>

#include "tests_constants.h"

using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;

// Assuming NUMBER_OF_TEST_JOBS is a compile-time constant
// NOLINTNEXTLINE(*-avoid-c-arrays)
boost::fibers::fiber fibers[NUMBER_OF_TEST_JOBS];

int main() {
  // Start timer
  auto start = high_resolution_clock::now();

  // Create a fiber for each job
  for (int i = 0; i < NUMBER_OF_TEST_JOBS; ++i) {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
    fibers[i] = boost::fibers::fiber([i]() {
      if ((i + 1) % PRINT_EVERY_NUMBER == 0) {
        std::cout << "I am " << i + 1 << "th job\n";
      }
    });
  }

  // Join all fibers
  for (auto& fiber : fibers) {
    if (fiber.joinable()) {
      fiber.join();
    }
  }

  // Stop timer
  auto end = std::chrono::high_resolution_clock::now();

  // Calculate elapsed time
  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();

  std::cout << "Execution took " << duration << " milliseconds.\n";

  return 0;
}
