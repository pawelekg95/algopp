cmake_minimum_required(VERSION 3.14)

add_library(calgopp-function EXCLUDE_FROM_ALL
        LinearFunction.cpp)

add_library(calgopp::function ALIAS calgopp-function)

target_link_libraries(calgopp-function
        PUBLIC calgopp::types
        PRIVATE)

target_include_directories(calgopp-function
        PUBLIC include
        )
