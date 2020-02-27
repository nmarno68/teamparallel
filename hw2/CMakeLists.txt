# Sets the cmake version required
cmake_minimum_required(VERSION 2.8)

# Names the project
project(hw2)

# Binary files will output to the bin directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

# Sets flags, to be used for different targets
set(COMMON_FLAGS, " -O3 -Wall -Wextra -pedantic ") # ALL will have these
set(SERIAL_FLAGS, "")
set(OPENMP_FLAGS, " -fopenmp ")
set(MPI_FLAGS, "")
set(GPU_FLAGS, "")
set(AUTOGRADER_FLAGS, "")

# For changing compiler
set(COMMON_COMPILER, "g++")

# Actually set common flags
add_compile_options("${COMMON_FLAGS}")

# Set compiler to g++
#set(CMAKE_CXX_COMPILER, "${COMMON_COMPILER}")

# Set shared libraries to be compiled only once.
#   STATIC -> .a
#   SHARED -> .so
#add_library(thing STATIC src/thing.cpp)
#add_library(common STATIC src/common.cpp include/chunk.h)
add_library(chunk STATIC src/chunk.cpp include/chunk.h)

# Make target serial
add_executable(serial src/serial.cpp include/common.h include/chunk.h)
target_compile_options(serial
        PRIVATE "${SERIAL_FLAGS}")
#        PRIVATE "${COMMON_FLAGS} ${SERIAL_FLAGS}")
target_link_libraries(serial common chunk)

# Make target "Hello world"!
#add_executable(hello src/helloworld.cpp include/thing.h)
#target_link_libraries(hello common thing)






