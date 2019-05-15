#include "test-utils.h"

#include <stdlib.h>
#include <stdarg.h>

void **build_arr(int n, ...) {
    va_list vl;
    int i;
    void **arr;

    if (n <= 0) {
        return NULL;
    }

    arr = malloc(n * sizeof(void *));

    va_start(vl, n);
    for (i = 0; i < n; i++) {
        arr[i] = va_arg(vl, void *);
    }
    va_end(vl);

    return arr;
}

