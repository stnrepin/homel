cmake_minimum_required(VERSION 3.10)

file(GLOB test_lib_source_files
    RELATIVE
    ${CMAKE_CURRENT_LIST_DIR}
    "*.c"
)

add_library(homel_test_lib STATIC ${test_lib_source_files})
target_include_directories(homel_test_lib
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
target_link_libraries(homel_test_lib sqlite3 unity)

add_subdirectory("file")
add_subdirectory("menu")
add_subdirectory("file-list")
add_subdirectory("db-controller")

