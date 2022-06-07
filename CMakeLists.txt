cmake_minimum_required(VERSION 3.22)
project(miniushell C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(miniushell
        lexer.c
        lexer.h
        minishell.c
        minishell.h)
