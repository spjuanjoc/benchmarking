set(SUBTEST_NAME map.tests)
add_executable(${SUBTEST_NAME} ../main.test.cpp map.test.cpp)

## Compiler options
include(../../cmake/CompilerOptions.cmake)
set_project_options(${SUBTEST_NAME})


## Find third-party packages
find_package(Catch2 REQUIRED)


#target_link_libraries(${SUBTEST_NAME} PRIVATE fmt::fmt)
target_compile_features(${SUBTEST_NAME} PUBLIC cxx_std_17)
target_include_directories(${SUBTEST_NAME} PRIVATE ${Catch2_INCLUDE_DIRS})

add_test(NAME ${SUBTEST_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${SUBTEST_NAME})
