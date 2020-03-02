cmake_minimum_required (VERSION 2.8)
project(silkstore-experiment)

set(CMAKE_VERBOSE_MAKEFILE ON)

#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")

macro(use_cxx14)
    if (CMAKE_VERSION VERSION_LESS "3.1")
        if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
            set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")
        endif ()
    else ()
        set (CMAKE_CXX_STANDARD 14)
    endif ()
endmacro(use_cxx14)

use_cxx14()

include_directories(include)


file(GLOB_RECURSE YCSB_SRC_FILES src/benchmark/ycsb/*.cpp)

file(GLOB_RECURSE KV_SRC_FILES src/kv/*.cpp)

add_executable (ycsb ${YCSB_SRC_FILES} ${KV_SRC_FILES})

target_link_libraries (ycsb tbb pthread tcmalloc)