include(FetchContent)
FetchContent_Declare(
        RAPIDJSON
        GIT_REPOSITORY  https://github.com/Tencent/rapidjson.git
        GIT_TAG         06d58b9e848c650114556a23294d0b6440078c61
)

FetchContent_GetProperties(RAPIDJSON)
if (NOT RAPIDJSON_POPULATED)
    FetchContent_Populate(RAPIDJSON)
endif ()

add_library(rapidjson INTERFACE)

target_include_directories(rapidjson
        INTERFACE ${rapidjson_SOURCE_DIR}/include
        )
