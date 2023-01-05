cmake_minimum_required(VERSION 3.14)

if(${GPU_PARALLEL} MATCHES "1")
    find_package(OpenCL REQUIRED)
    list(APPEND sources mathOpenCL.cpp)
else()
    list(APPEND sources math.cpp)
endif()

add_library(calgopp-math EXCLUDE_FROM_ALL
    ${sources}
    )

if(${GPU_PARALLEL} MATCHES "1")
    target_link_libraries(calgopp-math
            PRIVATE calgopp::gpu OpenCL::OpenCL)
endif()

add_library(calgopp::math ALIAS calgopp-math)

target_include_directories(calgopp-math
        PUBLIC include
        )
