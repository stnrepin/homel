cmake_minimum_required(VERSION 3.10)

project(homel LANGUAGES C)

add_subdirectory("src")
set_target_properties(homel
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)

if(BUILD_TEST)
    enable_testing()

    add_subdirectory("external/Unity")
    add_subdirectory("test")
endif()

