#include <tbb/parallel_for.h>

#include <chrono>
#include <iostream>

#include "tests_constants.h"

int main() {
	// Start timer
	auto start = std::chrono::high_resolution_clock::now();

	tbb::parallel_for(1, NUMBER_OF_TEST_JOBS + 1, [](int i) {
		if (i % PRINT_EVERY_NUMBER == 0) {
			std::cout << "i am " << i << "th job\n";
		}
	});

	// Stop timer
	auto end = std::chrono::high_resolution_clock::now();

	// Calculate elapsed time
	auto duration =
		std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
			.count();

	std::cout << "Execution took " << duration << " milliseconds.\n";

	return 0;
}
