cmake_minimum_required(VERSION 2.8)
project(ztest)
set(CMAKE_BUILD_TYPE "Debug")
set(sources main.cpp
	Zipper.cpp)
add_executable(${PROJECT_NAME} ${sources})
target_link_libraries(${PROJECT_NAME} z)
