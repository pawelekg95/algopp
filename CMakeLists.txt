cmake_minimum_required(VERSION 3.22)

include(cmake/Catch2.cmake)
include(cmake/toolchain.cmake)
include(cmake/rapidjson.cmake)
include(cmake/doxygen.cmake)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

if(${GPU_PARALLEL})
    message("GPU parallelization set")
else()
    message("No GPU parallelization set")
endif()

project(calgopp)

add_compile_options(-Wall -Wextra -Wpedantic -Werror $<$<COMPILE_LANGUAGE:CXX>:-std=c++17>)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_subdirectory(lib)
add_subdirectory(test/utils)
add_subdirectory(${APP})

doxygen_add_target(${CMAKE_CURRENT_SOURCE_DIR}/lib README.md)
