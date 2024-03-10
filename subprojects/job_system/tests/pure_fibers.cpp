#include <iostream>
#include <chrono>
#include <boost/fiber/all.hpp>
#include "tests_constants.h"

// Assuming NUMBER_OF_TEST_JOBS is a compile-time constant
boost::fibers::fiber fibers[NUMBER_OF_TEST_JOBS];

int main() {
	// Start timer
	auto start = std::chrono::high_resolution_clock::now();

	// Create a fiber for each job
	for (int i = 0; i < NUMBER_OF_TEST_JOBS; ++i) {
		fibers[i] = boost::fibers::fiber([i]() {
			if ((i + 1) % PRINT_EVERY_NUMBER == 0) {
				std::cout << "I am " << i + 1 << "th job\n";
			}
		});
	}

	// Join all fibers
	for (int i = 0; i < NUMBER_OF_TEST_JOBS; ++i) {
		if (fibers[i].joinable()) {
			fibers[i].join();
		}
	}

	// Stop timer
	auto end = std::chrono::high_resolution_clock::now();

	// Calculate elapsed time
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
			end - start).count();

	std::cout << "Execution took " << duration << " milliseconds.\n";

	return 0;
}
