cmake_minimum_required(VERSION 3.14)

if (GPU_PARALLEL)
    add_subdirectory(gpu)
endif()

add_subdirectory(types)
add_subdirectory(function)
add_subdirectory(signal)
add_subdirectory(approximation)
