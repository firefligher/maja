cmake_minimum_required(VERSION 3.9)
project(maja VERSION 1.0.0 DESCRIPTION "Lightweight image codec.")

add_library(
    maja SHARED
    src/huffmann.c
    src/fragment.c)

target_include_directories(maja PUBLIC include)
