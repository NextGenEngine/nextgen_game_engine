#include <benchmark/benchmark.h>

#include <memory>
#include <string>

#include "config_manager.h"

// Define your YAML content
static const std::string yamlContent = R"(
database:
  host: localhost
  port: 3306
)";

constexpr int ITERATIONS = 10000000;

class ConfigManagerBenchmark : public benchmark::Fixture {
 public:
  // NOLINTNEXTLINE(misc-non-private-member-variables-in-classes)
  std::unique_ptr<ConfigManager> configManager;

  void SetUp(const ::benchmark::State& /*unused*/) override {
    // Initialize configManager with YAML content here
    configManager =
        std::make_unique<ConfigManager>(ConfigManager_String(yamlContent));
  }

  void TearDown(const ::benchmark::State& state) override {
    // Cleanup code if necessary
  }
};

// Example usage of the fixture in a benchmark
BENCHMARK_DEFINE_F(ConfigManagerBenchmark, BM_getSetting_F_WARMUP)
(benchmark::State& state) {
  // NOLINTNEXTLINE(readability-identifier-length)
  for (auto _ : state) {
    (void)_;  // Explicitly mark the loop variable as unused
    auto host = configManager->getSetting<std::string>("database", "host");
    benchmark::DoNotOptimize(host);
  }
}
// NOLINTNEXTLINE(cppcoreguidelines-owning-memory, misc-use-anonymous-namespace)
BENCHMARK_REGISTER_F(ConfigManagerBenchmark, BM_getSetting_F_WARMUP)
    ->Unit(benchmark::kMicrosecond)
    ->Iterations(ITERATIONS);

// Example usage of the fixture in a benchmark
BENCHMARK_DEFINE_F(ConfigManagerBenchmark, BM_getSetting_F)
(benchmark::State& state) {
  // NOLINTNEXTLINE(readability-identifier-length)
  for (auto _ : state) {
    (void)_;  // Explicitly mark the loop variable as unused
    auto host = configManager->getSetting<std::string>("database", "host");
    benchmark::DoNotOptimize(host);
  }
}
// NOLINTNEXTLINE(cppcoreguidelines-owning-memory, misc-use-anonymous-namespace)
BENCHMARK_REGISTER_F(ConfigManagerBenchmark, BM_getSetting_F)
    ->Unit(benchmark::kMicrosecond)
    ->Iterations(ITERATIONS);

BENCHMARK_DEFINE_F(ConfigManagerBenchmark, BM_getSetting_Not_Inline_F)
(benchmark::State& state) {
  // NOLINTNEXTLINE(readability-identifier-length)
  for (auto _ : state) {
    (void)_;  // Explicitly mark the loop variable as unused
    auto host =
        configManager->getSetting_Not_Inline<std::string>("database", "host");
    benchmark::DoNotOptimize(host);
  }
}
// NOLINTNEXTLINE(cppcoreguidelines-owning-memory, misc-use-anonymous-namespace)
BENCHMARK_REGISTER_F(ConfigManagerBenchmark, BM_getSetting_Not_Inline_F)
    ->Unit(benchmark::kMicrosecond)
    ->Iterations(ITERATIONS);

// // Setup function to create ConfigManager instance with YAML string
// static void CustomSetUp(benchmark::State& state) {
//   state.PauseTiming();
//   // Setup code here. This code does not get timed
//   ConfigManager configManager = ConfigManager_String(yamlContent);
//   state.ResumeTiming();
// }

// Benchmark for getSetting
// NOLINTNEXTLINE(misc-use-anonymous-namespace)
static void BM_getSetting(benchmark::State& state) {
  ConfigManager configManager = ConfigManager_String(yamlContent);
  // NOLINTNEXTLINE(readability-identifier-length)
  for (auto _ : state) {
    (void)_;  // Explicitly mark the loop variable as unused
    auto host = configManager.getSetting<std::string>("database", "host");
    benchmark::DoNotOptimize(host);
  }
}
// NOLINTNEXTLINE(misc-use-anonymous-namespace, cppcoreguidelines-owning-memory)
BENCHMARK(BM_getSetting)->Unit(benchmark::kMicrosecond)->Iterations(ITERATIONS);

// Benchmark for getSetting_Not_Inline
// NOLINTNEXTLINE(misc-use-anonymous-namespace)
static void BM_getSetting_Not_Inline(benchmark::State& state) {
  ConfigManager configManager = ConfigManager_String(yamlContent);
  // NOLINTNEXTLINE(readability-identifier-length)
  for (auto _ : state) {
    (void)_;  // Explicitly mark the loop variable as unused
    auto host =
        configManager.getSetting_Not_Inline<std::string>("database", "host");
    benchmark::DoNotOptimize(host);
  }
}
// NOLINTNEXTLINE(cppcoreguidelines-owning-memory, misc-use-anonymous-namespace)
BENCHMARK(BM_getSetting_Not_Inline)
    ->Unit(benchmark::kMicrosecond)
    ->Iterations(ITERATIONS);

// Main function
// NOLINTNEXTLINE(modernize-avoid-c-arrays, cppcoreguidelines-avoid-c-arrays)
BENCHMARK_MAIN();
