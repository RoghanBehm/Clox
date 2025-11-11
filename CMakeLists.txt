cmake_minimum_required(VERSION 3.16)
project(Clox VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_library(clox_core STATIC
  src/chunk.c
  src/debug.c
  src/memory.c
  src/value.c
)
target_include_directories(clox_core PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(Clox src/main.c)
target_link_libraries(Clox PRIVATE clox_core)
