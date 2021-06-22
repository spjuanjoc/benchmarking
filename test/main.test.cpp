/**
 * @brief
 *
 * @author  juan.castellanos
 * @date    2021-06-19
 */

#define CATCH_CONFIG_MAIN  // Tell Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch2/catch.hpp>

TEST_CASE()
{
  std::string hello{"Hello"};

  REQUIRE(hello == "Hello");
  CHECK(hello != "world");
}