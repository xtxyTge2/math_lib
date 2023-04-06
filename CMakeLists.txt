cmake_minimum_required(VERSION 3.16.0)

project(math_lib)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

########################################################
# GOOGLE TEST
########################################################

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


enable_testing()

add_executable(
  rotations_test
  "src/rotations.cpp"
  
  "src/rotations_test.cpp"
)

target_link_libraries(
  rotations_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(rotations_test)
