cmake_minimum_required(VERSION 3.20)
project(PeppeSplines)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        PeppeSplines
        src/main.cpp
        src/parser.cpp
        src/writer.cpp
        src/splines.cpp
        src/intersection.cpp
)