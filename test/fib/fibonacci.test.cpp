/**
 * @brief micro-benchmark of different implementations of fibonacci.
 *
 * @author  juan.castellanos
 * @date    2021-06-21
 */

#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch2/catch.hpp>

#include <cmath>
#include <cstdint>

std::uint64_t regularFib(const std::uint64_t number)
{
  if (number == 0) return 0;
  if (number == 1) return 1;

  return regularFib(number - 1) + regularFib(number - 2);
}

constexpr std::uint64_t constexprFib(const std::uint64_t number)
{
  if (number == 0) return 0;
  if (number == 1) return 1;

  return constexprFib(number - 1) + constexprFib(number - 2);
}

std::uint64_t binetsFib(const double number)
{
  static const auto sqrt_5 = std::sqrt(5);

  if (number == 0) return 0;
  if (number == 1) return 1;

  return static_cast<std::uint64_t>(
    (std::pow(1 + sqrt_5, number) - std::pow(1 - sqrt_5, number)) /
    (std::pow(2, number) * sqrt_5));
}


TEST_CASE("should check a regular fib(n)", "[fibonacci]")
{
  CHECK(regularFib(0) == 0);
  CHECK(regularFib(1) == 1);
  CHECK(regularFib(6) == 8);
}

TEST_CASE("should check a constexpr fib(n)", "[fibonacci]")
{
  CHECK(constexprFib(0) == 0);
  CHECK(constexprFib(1) == 1);
  CHECK(constexprFib(6) == 8);
}

TEST_CASE("should check a Binet's fib(n)", "[fibonacci]")
{
  CHECK(binetsFib(0) == 0);
  CHECK(binetsFib(1) == 1);
  CHECK(binetsFib(6) == 8);
}

TEST_CASE("should benchmark different fib(15)", "[fibonacci]")
{
  BENCHMARK("regular fibonacci of 15") { return regularFib(25); };
  BENCHMARK("constexpr fibonacci of 15") { return constexprFib(25); };
  BENCHMARK("Binet's fibonacci of 15") { return binetsFib(25); };
}
