add_library(test-utils EXCLUDE_FROM_ALL
		helpers.cpp
		Chart.cpp
		)
		

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Charts REQUIRED)

target_include_directories(test-utils
        PUBLIC include)

target_link_libraries(test-utils
        PUBLIC Qt5::Widgets Qt5::Charts Qt5::Core calgopp::types)
        