include(FetchContent)
FetchContent_Declare(
    etl             SYSTEM
    GIT_REPOSITORY  https://github.com/ETLCPP/etl.git
    GIT_TAG         20.38.14
)

FetchContent_GetProperties(etl)
if (NOT etl_POPULATED)
    FetchContent_Populate(etl)
endif ()

add_library(etl INTERFACE)

# marked SYSTEM to exclude from clang-tidy analysis
target_include_directories(etl SYSTEM
    INTERFACE ${etl_SOURCE_DIR}/include
)

target_compile_options(etl
    INTERFACE -std=c++20 -w
)
