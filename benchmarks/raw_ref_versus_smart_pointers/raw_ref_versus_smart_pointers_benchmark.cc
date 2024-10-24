#include <benchmark/benchmark.h>

#include "raw_ref_versus_smart_pointers.h"

namespace {
// Constant for the number of times to run the benchmark
constexpr int num_iterations = 100000;

// Benchmark for the `references::runCalculation` function
static void BM_ReferencesCalculation(benchmark::State& state) {
  for (auto _ : state) {
    // Call the calculation function in the references namespace
    for (int i = 0; i < num_iterations; ++i) {
      benchmark::DoNotOptimize(references::runCalculation());
    }
  }
}
BENCHMARK(BM_ReferencesCalculation);

// Benchmark for the `smart_pointers::runCalculation` function
static void BM_SmartPointersCalculation(benchmark::State& state) {
  for (auto _ : state) {
    // Call the calculation function in the smart_pointers namespace
    for (int i = 0; i < num_iterations; ++i) {
      benchmark::DoNotOptimize(smart_pointers::runCalculation());
    }
  }
}
BENCHMARK(BM_SmartPointersCalculation);

}  // namespace

// Main function to run the benchmarks
BENCHMARK_MAIN();
