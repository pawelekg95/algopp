cmake_minimum_required(VERSION 3.14)

add_library(algopp-types EXCLUDE_FROM_ALL
        Point.cpp
        Peak.cpp
        )

add_library(algopp::types ALIAS algopp-types)

target_include_directories(algopp-types
        PUBLIC include
        )
