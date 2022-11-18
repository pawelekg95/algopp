add_library(test-utils EXCLUDE_FROM_ALL
		helpers.cpp
		)

target_include_directories(test-utils
        PUBLIC include)

target_link_libraries(test-utils
        PUBLIC calgopp::types rapidjson)
        