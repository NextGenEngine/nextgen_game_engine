#include <iostream>
#include <tbb/parallel_for.h>
#include "tests_constants.h"

int main()
{
    const int totalNumberOfJobs = NUMBER_OF_TEST_JOBS; // Adjust as needed

    tbb::parallel_for(1, totalNumberOfJobs + 1, [](int i)
                      {
        if (i % PRINT_EVERY_NUMBER == 0) {
            std::cout << "i am " << i << "th job\n";
        } });

    return 0;
}
