project(prusa-console)

cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

subdirs(extern/cpp-terminal)

include(FindPkgConfig)
pkg_check_modules(dbus-cxx REQUIRED dbus-cxx-2.0)
pkg_check_modules(sigc REQUIRED sigc++-3.0)

include_directories(${sigc_INCLUDE_DIRS} ${dbus-cxx_INCLUDE_DIRS})

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
    src/cz_prusa3d_sl1_printer0Proxy.cpp
    src/printer0Proxy.cpp
)

target_link_libraries(
    prusa-console-lib
    cpp-terminal
    dbus-cxx
    sigc-3.0
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
  tests/command_tests.cpp
)

target_link_libraries(
  tests
  GTest::gtest_main
  GTest::gmock_main
  prusa-console-lib
)

include(GoogleTest)
gtest_discover_tests(tests)
