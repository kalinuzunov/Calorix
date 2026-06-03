cmake_minimum_required(VERSION 3.15)
project(Calorix)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(model)
include_directories(.)

file(GLOB_RECURSE SOURCES "*.cpp" "*.h")

add_executable(Calorix ${SOURCES}
        model/Food.cpp
        model/Food.h
        model/UserBuilder.cpp
        model/UserBuilder.h
        model/FoodBuilder.cpp
        model/FoodBuilder.h)