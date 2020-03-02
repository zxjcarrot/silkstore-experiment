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
LINK_DIRECTORIES(/usr/local/lib)

file(GLOB_RECURSE YCSB_SRC_FILES src/benchmark/ycsb/*.cpp)

#file(GLOB_RECURSE LEVELDB_SRC_FILES src/kv/leveldb.cpp)
#file(GLOB_RECURSE PEBBLESDB_SRC_FILES src/kv/pebblesdb.cpp)
#file(GLOB_RECURSE WISCKEYDB_SRC_FILES src/kv/wisckey.cpp)

file(GLOB_RECURSE KV_SRC_FILES src/kv/*.cpp)

add_executable (leveldb_ycsb ${YCSB_SRC_FILES} ${KV_SRC_FILES})
target_link_libraries (leveldb_ycsb pthread leveldb)

add_executable (pebblesdb_ycsb ${YCSB_SRC_FILES} ${KV_SRC_FILES})
target_link_libraries (pebblesdb_ycsb pthread pebblesdb)

add_executable (wisckey_ycsb ${YCSB_SRC_FILES} ${KV_SRC_FILES})
target_link_libraries (wisckey_ycsb pthread wisckey)

# tbb tcmalloc