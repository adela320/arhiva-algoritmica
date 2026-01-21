cmake_minimum_required(VERSION 4.1)
project(LabirintX C)

set(CMAKE_C_STANDARD 11)

add_executable(LabirintX main.c)
target_compile_options(LabirintX PRIVATE -Wall)