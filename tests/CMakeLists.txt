function(ConfigureTest CMAKE_TEST_NAME)
  ADD_EXECUTABLE(${CMAKE_TEST_NAME} ${ARGN})
  TARGET_LINK_LIBRARIES(${CMAKE_TEST_NAME} spatial ${DEPS} gtest)
  ADD_TEST(NAME ${CMAKE_TEST_NAME} COMMAND ${CMAKE_TEST_NAME})
endfunction()

INCLUDE_DIRECTORIES(../spatial)

ConfigureTest(tree_test
  tree_test.cpp
)

ConfigureTest(rtree_test
  rtree_test.cpp
)

ConfigureTest(validation_test
  validation_test.cpp
)
