cmake_minimum_required(VERSION 3.14)

if (GPU_PARALLEL)
    add_subdirectory(gpu)
endif()

add_subdirectory(math)
add_subdirectory(algorithm)
add_subdirectory(types)
add_subdirectory(signal)
