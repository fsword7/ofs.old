cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CURRENT_LIST_DIR ON)

project(ofs)

#find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
#find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
#find_package(Vulkan REQUIRED)

add_subdirectory(src)
