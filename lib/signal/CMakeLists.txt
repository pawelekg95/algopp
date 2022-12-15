cmake_minimum_required(VERSION 3.14)

add_library(calgopp-signal EXCLUDE_FROM_ALL
		FourierTransform.cpp
        JacymirskiTransform.cpp
        Signal.cpp
        )

add_library(calgopp::signal ALIAS calgopp-signal)

target_include_directories(calgopp-signal
        PUBLIC include
        )

target_link_libraries(calgopp-signal
        PUBLIC calgopp::algorithm calgopp::types calgopp::math)
