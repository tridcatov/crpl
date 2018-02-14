CMAKE_MINIMUM_REQUIRED(VERSION 3.4)

project(rpl CXX)

#[[
set(HEADERS
    messages.h
    rpl.h
    node.h
    address.h
    rplInstance.h
    ioagent.h
    dummyioagent.h
    diomessage.h
    dismessage.h
    )
]]

file(GLOB HEADERS *.h)

#[[
set(SOURCES
    s.cpp
    rpl.cpp
    messages.cpp
    dummyioagent.cpp
    diomessage.cpp
    dismessage.cpp
    )
]]

file(GLOB SOURCES *.cpp)

add_definitions(-DLOGGING_ENABLED=1)
add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

