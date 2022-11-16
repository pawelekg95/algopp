cmake_minimum_required(VERSION 3.22)

include(cmake/Catch2.cmake)
include(cmake/toolchain.cmake)
include(cmake/rapidjson.cmake)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

project(calgopp)

add_compile_options(-Wall -Wextra -Wpedantic -Werror $<$<COMPILE_LANGUAGE:CXX>:-std=c++17>)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_subdirectory(lib)
add_subdirectory(test/utils)
add_subdirectory(${APP})
