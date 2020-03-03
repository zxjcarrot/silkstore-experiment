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

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

option(MAKE_LEVELDB         "make leveldb"  OFF)
option(MAKE_PEBBLESDB    "make pebblesdb" OFF)
option(MAKE_SILKSTORE    "make silkstore" OFF)
option(MAKE_WISCKEY    "make wisckey" OFF)

if (MAKE_LEVELDB)
    message(STATUS "Compile leveldb_ycsb...")
    file(GLOB_RECURSE LEVELDB_SRC_FILES src/kv/leveldb.cpp)
    add_definitions("-DISLEVELDB")
    add_executable (leveldb_ycsb ${YCSB_SRC_FILES} ${LEVELDB_SRC_FILES})
    target_link_libraries (leveldb_ycsb pthread leveldb)
    install(TARGETS leveldb_ycsb DESTINATION targets) 
elseif (MAKE_PEBBLESDB)
    message(STATUS "Compile pebblesdb_ycsb...")
    file(GLOB_RECURSE PEBBLESDB_SRC_FILES src/kv/pebblesdb.cpp)
    add_definitions("-DISPEBBLESDB")
    add_executable (pebblesdb_ycsb ${YCSB_SRC_FILES} ${PEBBLESDB_SRC_FILES})
    target_link_libraries (pebblesdb_ycsb pthread pebblesdb)
    install(TARGETS pebblesdb_ycsb DESTINATION targets) 
elseif (MAKE_SILKSTORE)
    message(STATUS "Compile silkstore_ycsb...")
    file(GLOB_RECURSE SILKSTORE_SRC_FILES src/kv/silkstore.cpp)
    add_definitions("-DISILKSTORE")
    add_executable (silkstore_ycsb ${YCSB_SRC_FILES} ${SILKSTORE_SRC_FILES})
    target_link_libraries (silkstore_ycsb pthread silkstore)
    install(TARGETS silkstore_ycsb DESTINATION targets) 
elseif (MAKE_WISCKEY)
    message(STATUS "Compile wisckey_ycsb...")
    file(GLOB_RECURSE WISCKEY_SRC_FILES src/kv/wisckey.cpp)
    add_definitions("-DISWISCKEY")
    add_executable (wisckey_ycsb ${YCSB_SRC_FILES} ${WISCKEY_SRC_FILES})
    target_link_libraries (wisckey_ycsb pthread wisckey)
    install(TARGETS wisckey_ycsb DESTINATION targets) 
endif ()

# tbb tcmalloc

