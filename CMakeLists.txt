cmake_minimum_required(VERSION 3.15)

project(areas
    VERSION 1.0.0
    LANGUAGES C CXX
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  add_compile_options(/std:c++17)
else ()
  add_compile_options(-Wall -Wextra -pedantic -std=c++17)
endif()

add_executable(areas
  src/main.cpp
  src/mesh.cpp
  src/parse.cpp
  src/triangle.cpp
  src/vector3.cpp
)
