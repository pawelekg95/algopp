cmake_minimum_required(VERSION 3.14)

list(APPEND sources FourierTransform.cpp JacymirskiTransform.cpp)

if(${GPU_PARALLEL} MATCHES "1")
    find_package(OpenCL REQUIRED)
    list(APPEND sources SignalOpenCL.cpp)
else()
    list(APPEND sources Signal.cpp)
endif()

add_library(calgopp-signal EXCLUDE_FROM_ALL
        ${sources}
        )

if(${GPU_PARALLEL} MATCHES "1")
    target_link_libraries(calgopp-math
            PRIVATE calgopp::gpu OpenCL::OpenCL)
endif()

add_library(calgopp::signal ALIAS calgopp-signal)

target_include_directories(calgopp-signal
        PUBLIC include
        )

target_link_libraries(calgopp-signal
        PUBLIC calgopp::algorithm calgopp::types calgopp::math)
