cmake_minimum_required(VERSION 3.14)

add_library(calgopp-function INTERFACE)

add_library(calgopp::function ALIAS calgopp-function)

target_link_libraries(calgopp-function
        INTERFACE calgopp::types)

target_include_directories(calgopp-function
        INTERFACE include
        )
