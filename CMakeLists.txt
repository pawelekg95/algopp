cmake_minimum_required(VERSION 3.22)

include(cmake/Catch2.cmake)
include(cmake/toolchain.cmake)
include(cmake/rapidjson.cmake)
include(cmake/doxygen.cmake)
include(cmake/etl.cmake)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

list(APPEND compile_options $<$<COMPILE_LANGUAGE:CXX>:-std=c++20>)

if(NOT DEFINED GPU_PARALLEL)
    list(APPEND compile_options -Wall -Wextra -Wpedantic -Werror $<$<COMPILE_LANGUAGE:CXX>:-std=c++20>)
    message("No GPU parallelization set. Bare CPU implementation\n")
else()
    message("GPU parallelization set. Using OpenCL implementation\n")
endif()

project(calgopp LANGUAGES C CXX)

add_compile_options(${compile_options})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_subdirectory(lib)
add_subdirectory(test/utils)
add_subdirectory(${APP})

doxygen_add_target(${CMAKE_CURRENT_SOURCE_DIR}/lib README.md)
