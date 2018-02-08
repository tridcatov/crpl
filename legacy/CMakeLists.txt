cmake_minimum_required(VERSION 3.4)

project(lrpl C)

#*********************************************************
# sources
#*********************************************************
include(ProjectConfigure)

set(INCLUDE_DIR include/rpl)

set(H
    platform.h
    rpl.h
    rpl-conf.h
    rpl-dag-root.h
    rpl-ns.h
    rpl-private.h
    uip.h
    rpl-types.h
)

foreach(HEADER ${H})
    set(HEADERS ${HEADERS} ${INCLUDE_DIR}/${HEADER})
endforeach(HEADER)

set(SOURCE_DIR src)

set(S
    rpl.c
    rpl-dag.c
    rpl-dag-root.c
    rpl-ext-header.c
    rpl-icmp6.c
    rpl-mrhof.c
    rpl-nbr-policy.c
    rpl-ns.c
    rpl-of0.c
    rpl-timers.c
)

foreach(SOURCE ${S})
    set(SOURCES ${SOURCES} ${SOURCE_DIR}/${SOURCE})
endforeach(SOURCE)

INCLUDE_DIRECTORIES(${INCLUDE_DIR})

add_definitions(-fPIC)
add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})
