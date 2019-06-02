#include "app-error.h"

#include <stdlib.h>
#include <stdio.h>

void handle_error(error_t err) {
    printf("Error: %s. Code: %d\n", get_message_by_code(err), (int)err);
}

void handle_fatal_error(error_t err) {
    printf("Fatal error: %s. Code %d\n", get_message_by_code(err), (int)err);
    exit(EXIT_SUCCESS);
}

char *get_message_by_code(error_t err) {
    switch (err) {
        case E_ALLOC:
            return "can't alloc memory";

        case E_SYSTEMEXIT:
            return "system exit";

        case E_INTERNAL:
            return "internal";

        default:
            return "unknown";
    }

    return NULL;
}

