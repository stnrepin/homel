#include "utils.h"

#include <stdlib.h>
#include <string.h>

#include "app-error.h"

char *strdup_(char *str) {
    size_t i;
    char *str_c;

    if (str == NULL) {
        str_c = NULL;
    }
    else {
        str_c = malloc((strlen(str) + 1) * sizeof(char));
        if (str_c == NULL) {
            handle_fatal_error(E_ALLOC);
        }

        i = 0;
        while ((str_c[i] = str[i]) != '\0') {
            i++;
        }
    }

    return str_c;
}

/* Taken from GNU Libc. */
char *strsep_(char **stringp, const char *delim) {
  char *begin, *end;

  begin = *stringp;
  if (begin != NULL) {
    end = begin + strcspn (begin, delim);

    if (*end) {
        *(end++) = '\0';
        *stringp = end;
    }
    else {
        *stringp = NULL;
    }
  }

  return begin;
}

int strcnt_(char *str, const char sym) {
    int count;

    count = 0;
    while (*str != '\0') {
        if (*str == sym) {
            count++;
        }
        str++;
    }

    return count;
}

char* str_repeat(char* str, size_t times) {
    char *ret = malloc((strlen(str) * times + 1) * sizeof(char));
    if (ret == NULL) {
        handle_fatal_error(E_ALLOC);
    }

    ret[0] = '\0';

    while (times-- > 0) {
        strcat(ret, str);
    }

    return ret;
}

void str_trunc(char *str, int max_len) {
    if ((int)strlen(str) > max_len) {
        str[max_len] = '~';
        str[max_len+1] = '\0';
    }
}

