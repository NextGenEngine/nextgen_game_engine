#include <iostream>
#include <vector>
#include <memory>
#include <tbb/parallel_for_each.h>
#include "../src/job.h"
#include "tests_constants.h"

class PrintJob : public Job
{
    int id;

public:
    PrintJob(int id) : id(id) {}

    void execute() override
    {
        if (id % 1000000 == 0)
        {
            std::cout << "i am " << id << "th job\n";
        }
    }
};

Job *jobs[NUMBER_OF_TEST_JOBS]; // Static array of Job pointers

int main()
{
    // Allocate and initialize jobs
    for (int i = 0; i < NUMBER_OF_TEST_JOBS; ++i)
    {
        jobs[i] = new PrintJob(i + 1);
    }

    // Execute the jobs in parallel
    tbb::parallel_for(0, NUMBER_OF_TEST_JOBS, [](int i)
                      { jobs[i]->execute(); });

    // Clean up
    for (int i = 0; i < NUMBER_OF_TEST_JOBS; ++i)
    {
        delete jobs[i]; // Manually delete allocated jobs
    }

    return 0;
}
