cmake_minimum_required(VERSION 3.14)

set(EXECUTABLE_NAME tests${EXE_EXTENSION})

add_executable(${EXECUTABLE_NAME}
        test.cpp
        )

target_link_libraries(${EXECUTABLE_NAME}
        PRIVATE calgopp::signal calgopp::types Catch2::Catch2WithMain test-utils)


add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/dataset_generator.py
        /tmp
        )
