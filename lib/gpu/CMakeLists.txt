cmake_minimum_required(VERSION 3.14)

find_package(OpenCL REQUIRED)

add_library(calgopp-gpu EXCLUDE_FROM_ALL
    Proxy.cpp
    )

target_link_libraries(calgopp-gpu
            PUBLIC OpenCL::OpenCL)

add_library(calgopp::gpu ALIAS calgopp-gpu)

target_include_directories(calgopp-gpu
        PUBLIC include
        )
