cmake_minimum_required(VERSION 3.14)

add_library(calgopp-types EXCLUDE_FROM_ALL
        Point.cpp
        Peak.cpp
        )

add_library(calgopp::types ALIAS calgopp-types)

target_include_directories(calgopp-types
        PUBLIC include
        )
