cmake_minimum_required(VERSION 3.10.1)
project(crpl)

file (GLOB C_SOURCES "*.c" )

add_library(${PROJECT_NAME} ${C_SOURCES})

