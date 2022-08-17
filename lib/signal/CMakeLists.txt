cmake_minimum_required(VERSION 3.14)

add_library(algopp-signal EXCLUDE_FROM_ALL
        Signal.cpp
        )

add_library(algopp::signal ALIAS algopp-signal)

target_include_directories(algopp-signal
        PUBLIC include
        )

target_link_libraries(algopp-signal
        PUBLIC algopp::types)
