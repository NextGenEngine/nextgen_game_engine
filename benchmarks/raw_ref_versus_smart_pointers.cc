#include <random>
std::random_device rd;   // Random device to seed the generator
std::mt19937 gen(rd());  // Standard Mersenne Twister generator

// Define a range for random numbers
std::uniform_int_distribution<> dis(1, 1000);  // Range of random numbers

// Generate four random values
int randomValue1 = dis(gen);
int randomValue2 = dis(gen);
int randomValue3 = dis(gen);
int randomValue4 = dis(gen);

namespace references {

// ServiceD has no dependencies
class ServiceD {
 public:
  ServiceD(int Long, int Int) : myLong(Long), myInt(Int) {}
  // Public members
  int myLong;
  int myInt;

  // No calculation needed, it holds its own values
  int calculate() { return myLong + myInt; }
};

// ServiceE has no dependencies
class ServiceE {
 public:
  ServiceE(int Long, int Int) : myLong(Long), myInt(Int) {}
  // Public members
  int myLong;
  int myInt;

  // No calculation needed, it holds its own values
  int calculate() { return myLong + myInt; }
};

// ServiceB depends on ServiceD
class ServiceB {
 public:
  ServiceB(ServiceD& d) : serviceD(d) {}

  // Public members
  int myLong{0};
  int myInt{0};

  // Calculate method sums the int and int from ServiceD
  int calculate() {
    myLong = serviceD.myLong;
    myInt = serviceD.myInt;
    return myLong + myInt;
  }

 private:
  ServiceD& serviceD;
};

// ServiceC depends on ServiceE
class ServiceC {
 public:
  ServiceC(ServiceE& serviceE) : serviceE(serviceE) {}

  // Public members
  int myLong{0};
  int myInt{0};

  // Calculate method sums the int and int from ServiceE
  int calculate() {
    myLong = serviceE.myLong;
    myInt = serviceE.myInt;
    return myLong + myInt;
  }

 private:
  ServiceE& serviceE;
};

// ServiceA depends on ServiceB and ServiceC
class ServiceA {
 public:
  ServiceA(ServiceB& b, ServiceC& c) : serviceB(b), serviceC(c) {}

  // Public members
  int myLong{0};
  int myInt{0};

  // Calculate method sums the int and int from ServiceB and ServiceC
  int calculate() {
    myLong = serviceB.myLong + serviceC.myLong;
    myInt = serviceB.myInt + serviceC.myInt;
    return myLong + myInt;
  }

 private:
  ServiceB& serviceB;
  ServiceC& serviceC;
};

// Top-level class containing references to the service classes
class TopLevelClass {
 public:
  TopLevelClass()
      : serviceD(randomValue1, randomValue2),
        serviceE(randomValue3, randomValue4),
        serviceA(serviceB,
                 serviceC),    // ServiceA depends on ServiceB and ServiceC
        serviceB(serviceD),    // ServiceB depends on ServiceD
        serviceC(serviceE) {}  // ServiceC depends on ServiceE

  // Call calculate() on each class in the hierarchy
  int calculateAll() {
    return serviceD.calculate() + serviceE.calculate() + serviceB.calculate() +
           serviceC.calculate() + serviceA.calculate();
  }

 private:
  ServiceD serviceD;
  ServiceE serviceE;
  ServiceA serviceA;
  ServiceB serviceB;
  ServiceC serviceC;
};

// Global variable for TopLevelClass
TopLevelClass topLevelInstance;

// Function to call the calculate method of TopLevelClass
int runCalculation() { return topLevelInstance.calculateAll(); }

}  // namespace references

#include <memory>
#include <utility>

namespace smart_pointers {

// Full class definitions must be provided before accessing their members

// ServiceD has no dependencies
class ServiceD {
 public:
  ServiceD(int Long, int Int) : myLong(Long), myInt(Int) {}
  // Public members
  int myLong;
  int myInt;

  // No calculation needed, it holds its own values
  int calculate() { return myLong + myInt; }
};

// ServiceE has no dependencies
class ServiceE {
 public:
  ServiceE(int Long, int Int) : myLong(Long), myInt(Int) {}
  // Public members
  int myLong;
  int myInt;

  // No calculation needed, it holds its own values
  int calculate() { return myLong + myInt; }
};

// ServiceB depends on ServiceD
class ServiceB {
 public:
  ServiceB(std::shared_ptr<ServiceD> d) : serviceD(std::move(d)) {}

  // Public members
  int myLong{0};
  int myInt{0};

  // Calculate method sums the int and int from ServiceD
  int calculate() {
    myLong = serviceD->myLong;
    myInt = serviceD->myInt;
    return myLong + myInt;
  }

 private:
  std::shared_ptr<ServiceD> serviceD;
};

// ServiceC depends on ServiceE
class ServiceC {
 public:
  ServiceC(std::shared_ptr<ServiceE> e) : serviceE(std::move(e)) {}

  // Public members
  int myLong{0};
  int myInt{0};

  // Calculate method sums the int and int from ServiceE
  int calculate() {
    myLong = serviceE->myLong;
    myInt = serviceE->myInt;
    return myLong + myInt;
  }

 private:
  std::shared_ptr<ServiceE> serviceE;
};

// ServiceA depends on ServiceB and ServiceC
class ServiceA {
 public:
  ServiceA(std::shared_ptr<ServiceB> b, std::shared_ptr<ServiceC> c)
      : serviceB(std::move(b)), serviceC(std::move(c)) {}

  // Public members
  int myLong{0};
  int myInt{0};

  // Calculate method sums the int and int from ServiceB and ServiceC
  int calculate() {
    myLong = serviceB->myLong + serviceC->myLong;
    myInt = serviceB->myInt + serviceC->myInt;
    return myLong + myInt;
  }

 private:
  std::shared_ptr<ServiceB> serviceB;
  std::shared_ptr<ServiceC> serviceC;
};

// Top-level class containing shared pointers to the service classes
class TopLevelClass {
 public:
  TopLevelClass()
      : serviceD(std::make_shared<ServiceD>(randomValue1, randomValue2)),
        serviceE(std::make_shared<ServiceE>(randomValue3, randomValue4)),
        serviceB(std::make_shared<ServiceB>(serviceD)),
        serviceC(std::make_shared<ServiceC>(serviceE)),
        serviceA(std::make_shared<ServiceA>(serviceB, serviceC)) {}

  // Call calculate() on each class in the hierarchy
  int calculateAll() {
    return serviceD->calculate() + serviceE->calculate() +
           serviceB->calculate() + serviceC->calculate() +
           serviceA->calculate();
  }

 private:
  std::shared_ptr<ServiceD> serviceD;
  std::shared_ptr<ServiceE> serviceE;
  std::shared_ptr<ServiceB> serviceB;
  std::shared_ptr<ServiceC> serviceC;
  std::shared_ptr<ServiceA> serviceA;
};

// Managed variable for TopLevelClass (recommended approach using smart
// pointers)
static std::shared_ptr<TopLevelClass> topLevelInstance =
    std::make_shared<TopLevelClass>();

// Function to call the calculate method of TopLevelClass
int runCalculation() { return topLevelInstance->calculateAll(); }

}  // namespace smart_pointers

#include <benchmark/benchmark.h>

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

// Main function to run the benchmarks
BENCHMARK_MAIN();
