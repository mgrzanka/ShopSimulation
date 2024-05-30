cmake_minimum_required(VERSION 3.25.1)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)

set(This tests)
set(Tests
    test_store.cpp)

add_executable(tests ${Tests})
target_link_libraries(tests PUBLIC Projekt gtest_main)

add_test(
  NAME test1
  COMMAND ${This}
)

