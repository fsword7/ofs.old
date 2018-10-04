cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

project(ofs)

find_package(SDL2 REQUIRED)
#find_package(OpenGL REQUIRED)
find_package(Vulkan REQUIRED)

add_subdirectory(src)
