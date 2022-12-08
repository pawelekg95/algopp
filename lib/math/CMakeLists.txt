cmake_minimum_required(VERSION 3.14)

add_library(calgopp-math INTERFACE)

add_library(calgopp::math ALIAS calgopp-math)

target_include_directories(calgopp-math
        INTERFACE include
        )
