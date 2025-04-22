cmake_minimum_required(VERSION 3.27)
project(project_to_upload C)

set(CMAKE_C_STANDARD 23)

add_executable(project_to_upload main.c
        exe1.c
        exe2.c
        exe3.c
        exe4.c
        files.h
)
