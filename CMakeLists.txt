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
    src/command_tree.cpp
    src/command_tree_builder.cpp
    src/concrete_commands.cpp
    src/cli.cpp
    src/history.cpp
    src/main.cpp
    src/key_actions.cpp
    src/printer.cpp
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
  tests/command_tree_tests.cpp
  tests/key_actions_tests.cpp
)

target_link_libraries(
  tests
  GTest::gtest_main
  prusa-console-lib
)

include(GoogleTest)
gtest_discover_tests(tests)
