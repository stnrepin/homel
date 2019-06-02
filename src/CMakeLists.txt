cmake_minimum_required(VERSION 3.10)

file(GLOB_RECURSE source_files
    RELATIVE
    ${CMAKE_CURRENT_LIST_DIR}
    "*.c"
)
list(REMOVE_ITEM source_files "main.c")

add_library(homel_lib STATIC ${source_files})

target_include_directories(homel_lib
    PUBLIC
    "${CMAKE_CURRENT_LIST_DIR}/../include"
    PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/sqlite3"
)

add_executable(homel "main.c")
target_link_libraries(homel homel_lib sqlite3)

