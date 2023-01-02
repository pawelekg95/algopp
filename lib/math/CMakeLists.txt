cmake_minimum_required(VERSION 3.14)

if(${GPU_PARALLEL})
        list(APPEND sources mathParallel.cpp)
else()
        list(APPEND sources mathBare.cpp)
endif()

add_library(calgopp-math EXCLUDE_FROM_ALL
        mathCommon.cpp
        ${sources}
        )

add_library(calgopp::math ALIAS calgopp-math)

target_include_directories(calgopp-math
        PUBLIC include
        )
