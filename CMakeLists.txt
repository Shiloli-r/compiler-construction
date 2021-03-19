cmake_minimum_required(VERSION 3.17)
project(compiler_construction C)

set(CMAKE_C_STANDARD 99)

file(GLOB SOURCES_SRC sources/*.c)

include_directories(include)
include_directories(sources)

add_executable(compiler programs/compiler.c)

add_library(sources STATIC ${SOURCES_SRC})
target_link_libraries(compiler sources)
