cmake_minimum_required(VERSION 3.4)

project(client CXX)

#*********************************************************
# sources
#*********************************************************
include(ProjectConfigure)

set(SOURCES
    main.cpp
)

add_definitions(-fPIC)
add_definitions(-DLOGGING_ENABLED=1)
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
