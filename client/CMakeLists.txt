cmake_minimum_required(VERSION 3.4)

project(client CXX)

#*********************************************************
# sources
#*********************************************************
include(ProjectConfigure)

file(GLOB HEADERS *.h)
file(GLOB SOURCES *.cpp)

add_definitions(-fPIC)
add_definitions(-DLOGGING_ENABLED=1)
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
add_dependencies(${PROJECT_NAME} rpl)
target_link_libraries(${PROJECT_NAME} rpl)
