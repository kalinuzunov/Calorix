cmake_minimum_required(VERSION 3.15)
project(Calorix)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(Calorix_Project/model)
include_directories(.)

file(GLOB_RECURSE SOURCES "*.cpp" "*.h")

add_executable(Calorix ${SOURCES}
        Calorix_Project/model/Food.cpp
        Calorix_Project/model/Food.h
        Calorix_Project/model/FoodBuilder.cpp
        Calorix_Project/model/FoodBuilder.h
        Calorix_Project/model/Exercise.cpp
        Calorix_Project/model/Exercise.h
        Calorix_Project/model/FoodEntry.cpp
        Calorix_Project/model/FoodEntry.h
        Calorix_Project/model/ExerciseEntry.cpp
        Calorix_Project/model/ExerciseEntry.h
        Calorix_Project/model/UserProfile.cpp
        Calorix_Project/model/UserProfile.h
        Calorix_Project/model/Trainee.cpp
        Calorix_Project/model/Trainee.h)