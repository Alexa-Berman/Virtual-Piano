cmake_minimum_required(VERSION 3.20)

project(M4OEP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(src)


add_compile_definitions(PROJECT_ROOT="${CMAKE_SOURCE_DIR}")