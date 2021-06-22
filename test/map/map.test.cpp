/**
 * @brief micro-benchmark of different implementations to look up in a map.
 *
 * @author  juan.castellanos
 * @date    2021-06-19
 */

#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch2/catch.hpp>

#include <array>
#include <map>
#include <string_view>

using namespace std::literals::string_view_literals;

std::map<std::string, int> regular_map{{
  {"black", 7},
  {"blue", 3},
  {"cyan", 5},
  {"green", 2},
  {"magenta", 6},
  {"red", 1},
  {"white", 8},
  {"yellow", 4},
}};

static const std::map<std::string, int> const_map{{
  {"black", 7},
  {"blue", 3},
  {"cyan", 5},
  {"green", 2},
  {"magenta", 6},
  {"red", 1},
  {"white", 8},
  {"yellow", 4},
}};

static constexpr std::array<std::pair<std::string_view, int>, 8> color_values{{
  {"black", 7},
  {"blue", 3},
  {"cyan", 5},
  {"green", 2},
  {"magenta", 6},
  {"red", 1},
  {"white", 8},
  {"yellow", 4},
}};

int lookupValueAt(const std::string_view key)
{
  static const auto map = std::map<std::string_view, int>{std::begin(color_values), std::end(color_values)};

  return map.at(key);
}

int lookupValueIndex(const std::string_view key)
{
  static auto map = std::map<std::string_view, int>{std::begin(color_values), std::end(color_values)};

  return map[key];
}

int findRegularMap(const std::string& key)
{
  const auto it = regular_map.find(key);

  if (it != regular_map.end())
  {
    return it->second;
  }
  else
  {
    throw std::runtime_error("Key not found");
  }
}

int findConstMap(const std::string& key)
{
  const auto it = const_map.find(key);

  if (it != const_map.end())
  {
    return it->second;
  }
  else
  {
    throw std::runtime_error("Key not found");
  }
}

TEST_CASE("should benchmark a map find()", "[find]")
{
  BENCHMARK("constexpr lookup .at()") { lookupValueAt("red"); };
  BENCHMARK("constexpr lookup []") { lookupValueIndex("red"); };
  BENCHMARK("Old way find regular map") { findRegularMap("red"); };
  BENCHMARK("Old way find const map") { findConstMap("red"); };
}
