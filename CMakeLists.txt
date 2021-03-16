cmake_minimum_required(VERSION 3.17)
project(GrpCPP)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(GrpCPP
        main.cpp
        main.h)
