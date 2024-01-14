cmake_minimum_required(VERSION 3.26)
project(untitled2 C)

set(CMAKE_C_STANDARD 17)

add_executable(untitled2 main.c
        image_processing.c
        image.c
        image.h)
