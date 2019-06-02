find_package (Threads)

add_library(sqlite3
    sqlite3.c
    sqlite3.h
)

target_include_directories(
    sqlite3
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}"
)
target_link_libraries(sqlite3 ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})
