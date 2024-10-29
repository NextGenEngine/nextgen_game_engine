#include <benchmark/benchmark.h>
#include <yaml-cpp/exceptions.h>

#include <exception>
#include <fstream>
#include <iostream>
#include <memory>
#include <optional>
#include <string>

#include "components/configuration/config_loader.h"
#include "components/configuration/config_repo.h"
#include "config_manager_move.h"

// Define your YAML content
static const std::string yamlContent = R"(
database:
  host: localhost
  port: 3306
)";

constexpr int ITERATIONS = 1000000;

using nextgen::engine::configuration::ConfigRepository;
using nextgen::engine::configuration::StringLoader;

auto CreateConfigManager() -> std::optional<std::shared_ptr<ConfigManager>> {
  while (true) {
    try {
      auto configManager = std::make_shared<ConfigManager>(
          std::make_unique<StringLoader>(yamlContent));
      return configManager;  // Successfully created, return it
    } catch (const YAML::BadFile& e) {
      std::cerr << "Failed to load or create the config file: " << e.what()
                << ". Retrying..." << '\n';
      // You might want to include a sleep here to prevent a tight retry loop
      std::ofstream const give_me_a_name("config.yaml");
      std::cerr << "Configuration file config.yaml created" << '\n';
    } catch (const std::exception& e) {
      std::cerr << "An unexpected error occurred: " << e.what() << '\n';
      return std::nullopt;
    }
  }
}

auto CreateConfigManager_Move() -> std::optional<
    move_semantics::ConfigManager<move_semantics::StringLoader>> {
  while (true) {
    try {
      auto configManager = move_semantics::ConfigManager(
          move_semantics::StringLoader(), yamlContent);
      return configManager;  // Successfully created, return it
    } catch (const YAML::BadFile& e) {
      std::cerr << "Failed to load or create the config file: " << e.what()
                << ". Retrying..." << '\n';
      // You might want to include a sleep here to prevent a tight retry loop
      std::ofstream const give_me_a_name("config.yaml");
      std::cerr << "Configuration file config.yaml created" << '\n';
    } catch (const std::exception& e) {
      std::cerr << "An unexpected error occurred: " << e.what() << '\n';
      return std::nullopt;
    }
  }
}

inline void DoTestIteration(auto configManager, auto componentConfig) {
  auto host = (*configManager)["database"]["host"];
  componentConfig = componentConfig.getSubConfig("module_subconfig");
  benchmark::DoNotOptimize(host);
  benchmark::DoNotOptimize(componentConfig);
}

inline void DoTestIterationShared(auto configManager, auto componentConfig) {
  auto host = configManager["database"]["host"];
  componentConfig = componentConfig.getSubConfig("module_subconfig");
  benchmark::DoNotOptimize(host);
  benchmark::DoNotOptimize(componentConfig);
}

// Benchmark for getSetting_Not_Inline
// NOLINTNEXTLINE(misc-use-anonymous-namespace)
static void BM_CONFIG_MANAGER_MOVE(benchmark::State& state) {
  auto configManager = CreateConfigManager_Move();
  if (!configManager.has_value()) {
    return;
  }
  auto componentConfig = configManager->getComponentConfig();
  // NOLINTNEXTLINE(readability-identifier-length)
  for (auto _ : state) {
    (void)_;  // Explicitly mark the loop variable as unused
    DoTestIterationShared(*configManager, componentConfig);
  }
}

// Benchmark for getSetting
// NOLINTNEXTLINE(misc-use-anonymous-namespace)
static void BM_CONFIG_MANAGER_REF(benchmark::State& state) {
  auto configManager = CreateConfigManager();
  if (!configManager.has_value()) {
    return;
  }
  auto componentConfig = (*configManager)->getComponentConfig();
  // NOLINTNEXTLINE(readability-identifier-length)
  for (auto _ : state) {
    (void)_;  // Explicitly mark the loop variable as unused
    DoTestIteration(*configManager, componentConfig);
  }
}

// WARMUP FIRST
// NOLINTNEXTLINE(cppcoreguidelines-owning-memory, misc-use-anonymous-namespace)
BENCHMARK(BM_CONFIG_MANAGER_MOVE)
    ->Unit(benchmark::kMicrosecond)
    ->Iterations(ITERATIONS);
// NOLINTNEXTLINE(cppcoreguidelines-owning-memory, misc-use-anonymous-namespace)
BENCHMARK(BM_CONFIG_MANAGER_MOVE)
    ->Unit(benchmark::kMicrosecond)
    ->Iterations(ITERATIONS);

// NOLINTNEXTLINE(misc-use-anonymous-namespace, cppcoreguidelines-owning-memory)
BENCHMARK(BM_CONFIG_MANAGER_REF)
    ->Unit(benchmark::kMicrosecond)
    ->Iterations(ITERATIONS);

// NOLINTNEXTLINE(misc-use-anonymous-namespace, cppcoreguidelines-owning-memory)
BENCHMARK(BM_CONFIG_MANAGER_REF)
    ->Unit(benchmark::kMicrosecond)
    ->Iterations(ITERATIONS);

// Main function
// NOLINTNEXTLINE(modernize-avoid-c-arrays, cppcoreguidelines-avoid-c-arrays)
BENCHMARK_MAIN();
