#include "utils.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#include "app-error.h"

char *read_line(int *len) {
    return file_read_line(stdin, len);
}

char *file_read_line(FILE *f, int *str_len) {
    size_t buf_size, new_buf_size, i;
    char c, *new_str, *str;
    int will_overflow;

    *str_len = 0;
    buf_size = 256;
    str = malloc(buf_size * sizeof(char));

    i = 0;
    while (1) {
        if (buf_size == i) {
            if (buf_size == SIZE_MAX) {
                handle_fatal_error(E_ALLOC);
            }

            will_overflow = (buf_size >> (sizeof(size_t) * 8 - 1)) == 1;
            new_buf_size = will_overflow ? SIZE_MAX : buf_size*2;

            new_str = (char *)realloc(str, new_buf_size);
            if (new_str == NULL) {
                handle_fatal_error(E_ALLOC);
            }

            *str_len = strlen(str);
            str = new_str;
        }

        c = fgetc(f);
        if (c == '\n' || c == EOF) {
            *str_len = i;
            str[i++] = '\0';
            return str;
        }

        str[i++] = c;
        *str_len = strlen(str);
    }
    return str;
}

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

error_t str_validate(char *str, char *whilelist) {
    error_t err;
    int is_empty_str;

    is_empty_str = 1;
    err = SUCCESS;

    while (*str != '\0' && SUCC(err)) {
        if (!(char_is_valid(*str) || strchr(whilelist, *str) != NULL)) {
            err = E_INVALID_STR;
        }
        str++;
        is_empty_str = 0;
    }

    if (is_empty_str) {
        err = E_INVALID_STR;
    }

    return err;
}

int char_is_valid(char c) {
    return  !(
                c == ':' || c == ';' ||
                c == '*' || c == '?' ||
                c == '"' || c == '|' ||
                c == '<' || c == '>' ||
                c == '+' || c == '%' ||
                c == '!' || c == '@'
             );
}
