cmake_minimum_required(VERSION 3.15)
project(Problem)

set(CMAKE_CXX_STANDARD 17)

add_executable(Komiwojazer main.cpp include/tsp.hpp)

include_directories(
        include
)

set(SOURCE_FILES
        src/tsp.cpp)

add_executable(komiwojazer_debug ${SOURCE_FILES} main.cpp)



