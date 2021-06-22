cmake_minimum_required(VERSION 3.19)
project(benchmarking_cpp VERSION 0.0.1 LANGUAGES CXX)


# Options
option(ENABLE_PCH   "Enable Precompiled Headers"  False)
option(ENABLE_TESTS "Enable tests"                False)


## Setup Conan
# Download automatically, you can also just copy the conan.cmake file
if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
      "${CMAKE_BINARY_DIR}/conan.cmake")
endif ()

include(${CMAKE_BINARY_DIR}/conan.cmake)
conan_cmake_run(CONANFILE conanfile.txt BASIC_SETUP NO_OUTPUT_DIRS)


## Check custom options
if (ENABLE_PCH) # Since CMake 3.15
  set(PC_HEADERS <vector> <string> <map> <utility> <algorithm> <cctype> <ostream> <memory> <sstream> <gtest/gtest.h>)
  target_precompile_headers(${PROJECT_NAME} INTERFACE ${PC_HEADERS})
  message("Pre compiled headers enabled")
endif ()

if (ENABLE_TESTS)
  message(STATUS "Tests enabled")
  enable_testing() # Must be placed before add_subdirectory
  add_subdirectory(test)
endif ()
