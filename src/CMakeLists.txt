cmake_minimum_required(VERSION 3.10)

file(GLOB_RECURSE source_files RELATIVE ${CMAKE_CURRENT_LIST_DIR} *.c)

add_executable(homel ${source_files})

