message(STATUS "Configuring project ${PROJECT_NAME}")
string(TOUPPER "${PROJECT_NAME}" PROJECT_PREFIX)
message(STATUS "Project prefix is set to ${PROJECT_PREFIX}")
#*********************************************************
# output directory
#*********************************************************
if(NOT OUTPUT_DIR)
    set(OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/output)
    message(STATUS "Setting output prefix to ${OUTPUT_DIR} because no global definition provided")
endif()
#*********************************************************
# BITNESS
#*********************************************************
if(NOT BITNESS)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(BITNESS 64)
        add_definitions ("-D${PROJECT_PREFIX}_X64")
        message(STATUS "Bitness: 64 bit")
    else()
        set(BITNESS 32)
        add_definitions ("-D${PROJECT_PREFIX}_X86")
        message(STATUS "Bitness: 32 bit")
    endif()
endif()
#*********************************************************
# output file prefixes
#*********************************************************
if(BITNESS EQUAL 32)
    set(${PROJECT_PREFIX}_RELEASE_POSTFIX        "")
    set(${PROJECT_PREFIX}_DEBUG_POSTFIX          "-d")
    set(${PROJECT_PREFIX}_MINSIZEREL_POSTFIX     "-rm")
    set(${PROJECT_PREFIX}_RELWITHDEBINFO_POSTFIX "-rd")
else()
    set(${PROJECT_PREFIX}_RELEASE_POSTFIX        "64")
    set(${PROJECT_PREFIX}_DEBUG_POSTFIX          "64-d")
    set(${PROJECT_PREFIX}_MINSIZEREL_POSTFIX     "64-rm")
    set(${PROJECT_PREFIX}_RELWITHDEBINFO_POSTFIX "64-rd")
endif()

set(CMAKE_RELEASE_POSTFIX           ${${PROJECT_PREFIX}_RELEASE_POSTFIX})
set(CMAKE_DEBUG_POSTFIX             ${${PROJECT_PREFIX}_DEBUG_POSTFIX})
set(CMAKE_MINSIZEREL_POSTFIX        ${${PROJECT_PREFIX}_MINSIZEREL_POSTFIX})
set(CMAKE_RELWITHDEBINFO_POSTFIX    ${${PROJECT_PREFIX}_RELWITHDEBINFO_POSTFIX})

#*********************************************************
# output directories
#*********************************************************
message(STATUS "Binary artefacts shall be outputted into ${OUTPUT_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
