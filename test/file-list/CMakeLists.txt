cmake_minimum_required(VERSION 3.10)

add_executable(homel_test_file-list "test_file-list.c")
target_link_libraries(homel_test_file-list homel_test_lib homel_lib)

add_test(test_file-list homel_test_file-list)

