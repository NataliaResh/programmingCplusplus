cmake_minimum_required(VERSION 3.14)
project(my_project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set (gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  test_suite
  tests/test_suite.cpp
)

target_link_libraries(
  test_suite
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_suite)

option(ENABLE_SANITIZERS "Enable Address, Undefined Behavior, and Memory Leak sanitizers" OFF)
if (ENABLE_SANITIZERS)
    set(SANITIZER_FLAGS "-fsanitize=leak,address,undefined") # set variable to list of options
    target_compile_options(test_suite PRIVATE ${SANITIZER_FLAGS}) # add compile options listed above to test_suite target
    target_link_options(test_suite PRIVATE ${SANITIZER_FLAGS}) # also you need list these options while linking files
endif()
