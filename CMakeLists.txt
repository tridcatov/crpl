CMAKE_MINIMUM_REQUIRED(VERSION 3.4)

project(crpl)

add_definitions(-Wall -Werror -Wextra)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/)

SET(OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/output)

INCLUDE_DIRECTORIES(
    common
    rpl
    )

add_definitions(-std=c++11)
ADD_SUBDIRECTORY(client)
ADD_SUBDIRECTORY(rpl)
