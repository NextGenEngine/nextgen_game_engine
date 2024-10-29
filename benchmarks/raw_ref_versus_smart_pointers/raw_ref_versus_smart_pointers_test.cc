#include "raw_ref_versus_smart_pointers.h"

#include <gtest/gtest.h>  // Assuming you're using GoogleTest

#include <memory>

namespace references {

TEST(TopLevelClassTest, CalculateAllWorks) {
  // Arrange: Create necessary dependencies with raw references
  ServiceD serviceD(randomValue1, randomValue2);
  ServiceE serviceE(randomValue3, randomValue4);
  ServiceB serviceB(serviceD);
  ServiceC serviceC(serviceE);
  ServiceA serviceA(serviceB, serviceC);

  // Act: Create the top-level class and call the calculateAll method
  TopLevelClass topLevel;  // Your setup already instantiates these services
  int const result = topLevel.calculateAll();

  // Assert: Check if the calculation is correct
  ASSERT_EQ(result, serviceD.calculate() + serviceE.calculate() +
                        serviceB.calculate() + serviceC.calculate() +
                        serviceA.calculate());
}

}  // namespace references

namespace smart_pointers {

TEST(TopLevelClassTest, CalculateAllWorks) {
  // Arrange: Create necessary dependencies with smart pointers
  auto serviceD = std::make_shared<ServiceD>(randomValue1, randomValue2);
  auto serviceE = std::make_shared<ServiceE>(randomValue3, randomValue4);
  auto serviceB = std::make_shared<ServiceB>(serviceD);
  auto serviceC = std::make_shared<ServiceC>(serviceE);
  auto serviceA = std::make_shared<ServiceA>(serviceB, serviceC);

  // Act: Create the top-level class and call the calculateAll method
  TopLevelClass topLevel;  // Already uses smart pointers internally
  int const result = topLevel.calculateAll();

  // Assert: Check if the calculation is correct
  ASSERT_EQ(result, serviceD->calculate() + serviceE->calculate() +
                        serviceB->calculate() + serviceC->calculate() +
                        serviceA->calculate());
}

}  // namespace smart_pointers
