cmake_minimum_required(VERSION 3.28)
project(UniMultiC)

set(CMAKE_CXX_STANDARD 17)

add_executable(UniMultiC
        main.c
        process_management.c
        text_analysis.c
        text_generation.c
        utilities.c)
