cmake_minimum_required(VERSION 3.26)
project(EX3 C)

set(CMAKE_C_STANDARD 11)

add_executable(EX3 main.c
        input_handler.c
        input_handler.h
        command_executor.c
        command_executor.h)
