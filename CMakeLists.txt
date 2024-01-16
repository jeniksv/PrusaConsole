project(prusa-console)

cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

subdirs(extern/cpp-terminal)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(
    prusa-console-lib
    src/command.cpp
    src/console_reader.cpp
    src/history.cpp
    src/main.cpp
    src/tab_completion.cpp
    src/key_actions.cpp
    src/printer.cpp
    src/parser.cpp
)

target_link_libraries(
    prusa-console-lib
    cpp-terminal
)

add_executable(
    prusa-console
    src/main.cpp
)

target_link_libraries(prusa-console prusa-console-lib)

subdirs(extern/googletest)

add_executable(
  tests
  tests/history_tests.cpp
  tests/tab_completion_tests.cpp
  tests/parser_tests.cpp
  tests/key_actions_tests.cpp
)

target_link_libraries(
  tests
  GTest::gtest_main
  prusa-console-lib
)

include(GoogleTest)
gtest_discover_tests(tests)
