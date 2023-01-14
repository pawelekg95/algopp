cmake_minimum_required(VERSION 3.14)

add_library(calgopp-approx EXCLUDE_FROM_ALL
        approximation.cpp)

add_library(calgopp::approx ALIAS calgopp-approx)

target_link_libraries(calgopp-approx
        PUBLIC calgopp::signal calgopp::function
        PRIVATE calgopp::algorithm calgopp::types)

target_include_directories(calgopp-approx
        PUBLIC include
        )
