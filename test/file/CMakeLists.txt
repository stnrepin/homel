cmake_minimum_required(VERSION 3.10)

add_executable(homel_test_file "test_file.c")
target_link_libraries(homel_test_file homel_test_lib homel_lib)

add_test(test_file homel_test_file)

