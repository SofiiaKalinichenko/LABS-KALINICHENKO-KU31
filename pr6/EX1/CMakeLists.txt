cmake_minimum_required(VERSION 3.26)
project(EX1 C)

set(CMAKE_C_STANDARD 11)

add_executable(EX1 main.c
        input_handler.h
        command_executor.h
        command_executor.c
        input_handler.c)
