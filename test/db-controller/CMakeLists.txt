cmake_minimum_required(VERSION 3.10)

add_executable(homel_test_db-controller "test_db-controller.c")
target_link_libraries(homel_test_db-controller homel_test_lib homel_lib)

add_test(test_db-controller homel_test_db-controller)

