cmake_minimum_required(VERSION 3.14)

add_library(calgopp-algorithm INTERFACE)

add_library(calgopp::algorithm ALIAS calgopp-algorithm)

target_include_directories(calgopp-algorithm
        INTERFACE include
        )

target_link_libraries(calgopp-algorithm
        INTERFACE calgopp::types)
