cmake_minimum_required(VERSION 4.1)
project(Pixeli_curba C)

set(CMAKE_C_STANDARD 11)

add_executable(Pixeli_curba main.c)
target_compile_options(Pixeli_curba PRIVATE -Wall)