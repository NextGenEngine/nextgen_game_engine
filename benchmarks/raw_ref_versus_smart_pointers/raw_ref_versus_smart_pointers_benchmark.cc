#include <benchmark/benchmark.h>

#include <iostream>

#include "raw_ref_versus_smart_pointers.h"

namespace {
// Constant for the number of times to run the benchmark
constexpr int num_iterations = 100000;

// Benchmark for the `references::runCalculation` function
void BM_ReferencesCalculation(benchmark::State& state) {
  for (auto _ : state) {
    // Call the calculation function in the references namespace
    for (int i = 0; i < num_iterations; ++i) {
      benchmark::DoNotOptimize(references::runCalculation());
    }
  }
}
BENCHMARK(BM_ReferencesCalculation);

// Benchmark for the `smart_pointers::runCalculation` function
void BM_SmartPointersCalculation(benchmark::State& state) {
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
// BENCHMARK_MAIN();

// Main function to print class sizes and run benchmarks
int main(int argc, char** argv) {
  // Print sizes of reference-based classes
  std::cout << "Sizes of reference-based classes:\n";
  std::cout << "ServiceD: " << sizeof(references::ServiceD) << " bytes\n";
  std::cout << "ServiceE: " << sizeof(references::ServiceE) << " bytes\n";
  std::cout << "ServiceB: " << sizeof(references::ServiceB) << " bytes\n";
  std::cout << "ServiceC: " << sizeof(references::ServiceC) << " bytes\n";
  std::cout << "ServiceA: " << sizeof(references::ServiceA) << " bytes\n";
  std::cout << "TopLevelClass: " << sizeof(references::TopLevelClass)
            << " bytes\n\n";

  // Print sizes of smart pointer-based classes
  std::cout << "Sizes of smart pointer-based classes:\n";
  std::cout << "ServiceD: " << sizeof(smart_pointers::ServiceD) << " bytes\n";
  std::cout << "ServiceE: " << sizeof(smart_pointers::ServiceE) << " bytes\n";
  std::cout << "ServiceB: " << sizeof(smart_pointers::ServiceB) << " bytes\n";
  std::cout << "ServiceC: " << sizeof(smart_pointers::ServiceC) << " bytes\n";
  std::cout << "ServiceA: " << sizeof(smart_pointers::ServiceA) << " bytes\n";
  std::cout << "TopLevelClass: " << sizeof(smart_pointers::TopLevelClass)
            << " bytes\n\n";

  // Run the benchmarks
  ::benchmark::Initialize(&argc, argv);
  ::benchmark::RunSpecifiedBenchmarks();
}
