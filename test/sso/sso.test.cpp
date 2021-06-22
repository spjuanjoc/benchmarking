/**
 * @brief micro-benchmark of different constructions for Small String Optimization.
 *
 * @author  juan.castellanos
 * @date    2021-06-19
 */

#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch2/catch.hpp>

#include <algorithm>
#include <cstdio>
#include <iostream>

TEST_CASE("should benchmark a small string construction", "[small_string][copy]")
{
  std::string small_string{"Small string"};

  BENCHMARK("Small string deep copy") { std::string s(small_string); };
  BENCHMARK("Small string const ref") { const std::string& s(small_string); };
  BENCHMARK("Small string const ref {}") { const std::string& s{small_string}; };
  BENCHMARK("Small string move") { const std::string s{std::move(small_string)}; };
  BENCHMARK("Small string view") { std::string_view s(small_string); };
}

TEST_CASE("should benchmark a big string construction", "[big_string][copy]")
{
  std::string big_string{R"(some big string with enough characters
 not to be optimized by the compiler
 not to be optimized by the compiler
 not to be optimized by the compiler
 not to be optimized by the compiler
 not to be optimized by the compiler
)"};

  BENCHMARK("Big string deep copy") { std::string s(big_string); };
  BENCHMARK("Big string const ref") { const std::string& s(big_string); };
  BENCHMARK("Big string const ref {}") { const std::string& s{big_string}; };
  BENCHMARK("Big string move") { const std::string s{std::move(big_string)}; };
  BENCHMARK("Big string view") { std::string_view s(big_string); };
}
