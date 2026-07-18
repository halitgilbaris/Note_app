cmake_minimum_required(VERSION 3.16)

project(Note_app)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(Note_app
    src/main.cpp
    src/note.cpp
    src/folder.cpp
)