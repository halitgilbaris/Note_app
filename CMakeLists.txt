cmake_minimum_required(VERSION 3.10)
project(Note_app)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(Note_app ${SOURCES}
    include/imgui_stdlib.h
    src/imgui_stdlib.cpp)

target_link_libraries(Note_app PRIVATE 
    glfw 
    OpenGL::GL 
    X11 
    pthread 
    dl
)
