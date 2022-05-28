cmake_minimum_required(VERSION 3.22)
project(PeppeSplines)

set(CMAKE_CXX_STANDARD 17)

#add_executable(PeppeSplines src/main.cpp src/splines.cpp src/splines.h src/newton.cpp src/newton.h src/parser.cpp src/parser.h)
add_executable(PeppeSplines src/main.cpp src/parser.cpp src/writer.cpp src/splines.cpp)