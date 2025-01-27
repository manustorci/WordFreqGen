cmake_minimum_required(VERSION 3.28)
project(UniMonoC C)

set(CMAKE_C_STANDARD 11)

add_executable(UniMonoC main.c
        text_analysis.c
        text_generation.c
        utilities.c
        text_analysis.h
        text_generation.h
        utilities.h)
