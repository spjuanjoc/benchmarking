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

/**
 * Small String in MSVC and GCC ~15 chars, in clang ~22
 */
TEST_CASE("should benchmark string copy", "[copy]")
{
  std::string small_string{"Small string"};    // 12 chars
  std::string big_string{"16+ sized string"};  // 16 chars
  auto size = sizeof(std::string);
  auto capacity = std::string().capacity();
  auto small = std::string(capacity, '*');
  auto big = std::string(capacity + 1, '*');

  std::clog << "sizeof  : " << size << '\n';
  std::clog << "Capacity: " << capacity << '\n';  // The max size of a Small String
  std::clog << "Small   : " << small.capacity() << '\n';
  std::clog << "Big     : " << big.capacity() << '\n';

  BENCHMARK("Small string copy") { std::string copy(small_string); };
  BENCHMARK("Big string copy") { std::string copy(big_string); };
}

TEST_CASE("should benchmark a small string copy construction", "[small_string][copy]")
{
  std::string small_string{"Small string"};

  BENCHMARK("Small string copy") { std::string s(small_string); return s;};
  BENCHMARK("Small string move") { const std::string s{std::move(small_string)}; };
  BENCHMARK("Small string view") { std::string_view s(small_string); return s;};
}

TEST_CASE("should benchmark a big string copy construction", "[big_string][copy]")
{
  std::string big_string{"some big string with enough characters"};

  BENCHMARK("Big string copy") { std::string s(big_string); return s;};
  BENCHMARK("Big string move") { std::string s{std::move(big_string)}; };
  BENCHMARK("Big string view") { std::string_view s(big_string); return s;};
}
