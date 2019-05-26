cmake_minimum_required(VERSION 3.10)

add_executable(homel_test_menu "test_menu.c")
target_link_libraries(homel_test_menu homel_test_lib homel_lib)

add_test(test_menu homel_test_menu)

