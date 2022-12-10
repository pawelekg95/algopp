cmake_minimum_required(VERSION 3.14)

add_library(calgopp-math EXCLUDE_FROM_ALL
        math.cpp
        )

add_library(calgopp::math ALIAS calgopp-math)

target_include_directories(calgopp-math
        PUBLIC include
        )
