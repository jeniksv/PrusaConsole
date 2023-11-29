project(prusa-console)

cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

subdirs(extern/cpp-terminal)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_executable(
    prusa-console 
    src/command.cpp
    src/console_reader.cpp
    src/history.cpp
    src/main.cpp
    src/tab_completion.cpp
)

target_link_libraries(prusa-console cpp-terminal)
