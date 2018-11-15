#
# This example demonstrates the installation process of a custom code that uses
# the ttHSW example package.
#

#
# Project setup
#
cmake_minimum_required(VERSION 2.6)
project(ntuple_st2)

#
# Some definitions below
#
# add_definitions(-DDEBUG)
list(APPEND CMAKE_MODULE_PATH "$ENV{CMAKE_MODULE_PATH}")

# per-lines to bring happiness for young&old cmake
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -pedantic -Wunused-variable")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunused-but-set-variable")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=sign-compare")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=return-type")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=missing-braces")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=delete-non-virtual-dtor")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

#
# find ttHSW
#
find_package(ttHSW)
add_ttHSW_lib(ttHSW-core)
add_ttHSW_lib(ttHSW-reconstruction)
add_ttHSW_lib(ttHSW-ttbar_reco_C)
add_ttHSW_lib(ttHSW-sp)

#
# Compilation targets
#
add_executable(ntuple_st2
    src/debug.cc
    src/main.cc
    src/stage2.cc
    src/producer.cc
#     src/dict/ntuple_dict.cc
    src/trees/io.cc
    src/trees/read.cc
    src/trees/write.cc)

#
# ROOT inclusion
#
# You need to tell CMake where to find the ROOT installation.
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS RIO Net)

#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(FindROOT)

include_directories($ENV{ROOTSYS}/include)
include_directories(include/ttH/)

#
# Find the needed libraries and add them for the linking
#
target_include_directories(ntuple_st2 PUBLIC include ${ttHSW_INCLUDE_DIRS})
target_link_libraries(ntuple_st2 ${ttHSW_LIBRARIES} ${ROOT_LIBRARIES})
