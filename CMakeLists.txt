cmake_minimum_required(VERSION 3.15)
project(potoki C)

set(CMAKE_C_STANDARD 11)

add_executable(potoki main.c parallelCounter/parallelCounter.c parallelCounter/parallelCounter.h trivialCounter/trivialCounter.h trivialCounter/trivialCounter.c)