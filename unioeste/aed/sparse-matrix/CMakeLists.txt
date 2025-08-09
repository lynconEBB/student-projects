cmake_minimum_required(VERSION 3.16)
project(SparseMatrix C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(SparseMatrix
        App.c
        App.h
        main.c
        Matrix.c
        Matrix.h)
