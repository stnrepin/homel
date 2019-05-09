#ifndef TEST_UTILS_H_
#define TEST_UTILS_H_

#include <stdarg.h>

#define BUILD_ARR(type, n, ...) ((type*)build_arr(n, __VA_ARGS__))

void **build_arr(int n, ...);

#endif /* TEST_UTILS_H_ */

