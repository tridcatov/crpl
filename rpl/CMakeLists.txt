CMAKE_MINIMUM_REQUIRED(VERSION 3.4)

project(rpl CXX)

file(GLOB_RECURSE HEADERS *.h)
file(GLOB_RECURSE SOURCES *.cpp)

set(DIRS
    options
    messages
    )

INCLUDE_DIRECTORIES(
    ${DIRS}
    )

add_definitions(-DLOGGING_ENABLED=1)
add_definitions(
    -DHEX_BUFFER_OCTETS_IN_GROUP=4
    -DHEX_BUFFER_GROUPS_IN_LINE=4)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${DIRS}
    )

