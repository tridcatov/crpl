cmake_minimum_required(VERSION 3.4)

project(crpl C)

#*********************************************************
# output directory
#*********************************************************
set(CRPL_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/output)

#*********************************************************
# BITNESS
#*********************************************************
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(BITNESS 64)
    add_definitions (-DCRPL_X64)
    message("Bitness: 64 bit")
else()
    set(BITNESS 32)
    add_definitions (-DCRPL_X86)
    message("Bitness: 32 bit")
endif()

#*********************************************************
# output file prefixes
#*********************************************************
if(BITNESS EQUAL 32)
    set(CRPL_RELEASE_POSTFIX        "")
    set(CRPL_DEBUG_POSTFIX          "-d")
    set(CRPL_MINSIZEREL_POSTFIX     "-rm")
    set(CRPL_RELWITHDEBINFO_POSTFIX "-rd")
else()
    set(CRPL_RELEASE_POSTFIX        "64")
    set(CRPL_DEBUG_POSTFIX          "64-d")
    set(CRPL_MINSIZEREL_POSTFIX     "64-rm")
    set(CRPL_RELWITHDEBINFO_POSTFIX "64-rd")
endif()

set(CMAKE_RELEASE_POSTFIX           ${CRPL_RELEASE_POSTFIX})
set(CMAKE_DEBUG_POSTFIX             ${CRPL_DEBUG_POSTFIX})
set(CMAKE_MINSIZEREL_POSTFIX        ${CRPL_MINSIZEREL_POSTFIX})
set(CMAKE_RELWITHDEBINFO_POSTFIX    ${CRPL_RELWITHDEBINFO_POSTFIX})

#*********************************************************
# output directories
#*********************************************************
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CRPL_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CRPL_OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CRPL_OUTPUT_DIR})

#*********************************************************
# sources
#*********************************************************
set(HEADERS
    src/platform.h
    src/rpl.h
    src/rpl-conf.h
    src/rpl-dag-root.h
    src/rpl-ns.h
    src/rpl-private.h
)

set(SOURCES
    src/rpl.c
    src/rpl-dag.c
    src/rpl-dag-root.c
    src/rpl-ext-header.c
    src/rpl-icmp6.c
    src/rpl-mrhof.c
    src/rpl-nbr-policy.c
    src/rpl-ns.c
    src/rpl-of0.c
    src/rpl-timers.c
)

add_library(crpl SHARED ${HEADERS} ${SOURCES})
