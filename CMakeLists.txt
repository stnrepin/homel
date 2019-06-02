cmake_minimum_required(VERSION 3.10)

project(homel LANGUAGES C)

# Build internal SQLite.
#
add_subdirectory(external/sqlite3)

if (BUILD_TEST)
    add_definitions(-DUNIT_TEST=1)
endif()

add_subdirectory("src")
set_target_properties(homel
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)

if(BUILD_TEST)
    enable_testing()

    add_subdirectory("external/Unity")

    if(WIN32)
        target_compile_definitions(unity PRIVATE UNITY_WEAK_ATTRIBUTE= UNITY_INCLUDE_SETUP_STUBS=)
    endif()

    add_subdirectory("test")
endif()

