#include "utils.h"

#include <stdlib.h>
#include <string.h>

#include "app-error.h"

char *strdup_(char *str) {
    char *str_c;

    if (str == NULL) {
        str_c = NULL;
    }
    else {
        str_c = malloc((strlen(str) + 1) * sizeof(char));
        if (str_c == NULL) {
            handle_fatal_error(E_ALLOC);
        }
    }

    return str_c;
}

