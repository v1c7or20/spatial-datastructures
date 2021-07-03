cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0048 OLD)
project(spatial_implementation)

set(CMAKE_CXX_STANDARD 11)

if (NOT TARGET gtest_main)
    add_subdirectory(googletest)
endif ()

include_directories(${gtest_SOURCE_DIR}/include ${gmock_SOURCE_DIR}/include)

enable_testing()

add_executable(
  tree_test
  tree_test.cpp
)

add_test(
  NAME tree_test
  COMMAND tree_test
)

target_link_libraries(
  tree_test
  gtest_main
  gtest
  gmock
)
