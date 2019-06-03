#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include <wchar.h>

#include "app-error.h"

/**
 * Обертка над read_line(FILE *f) для чтения из stdin.
 *
 * @param len Длина строки.
 * @return Строка.
 */
char *read_line(int *len);

/**
 * Читает строку произвольного размера из файла.
 *
 * @param f Файл.
 * @param str_len Размер прочитанной строки.
 * @return Строка.
 */
char *file_read_line(FILE *f, int *str_len);

/**
 * Создает копию строки
 *
 * @param str Строка.
 * @return Копия строки.
 */
char *strdup_(char *str);

/**
 * "Отрезает" от строки подстроку, заканчивающуюся на delim (не включается)
 * и возвращает эту подстроку.
 *
 * @param stringp Строка.
 * @param delim Разделитель.
 * @return Подстрока.
 */
char *strsep_(char **stringp, const char *delim);

/**
 * Возвращает количество вхождений символа в строке.
 *
 * @param str Строка.
 * @param sym Символ.
 * @return Количество вхождений.
 */
int strcnt_(char *str, const char sym);

/**
 * Повторяет строку times раз.
 *
 * @param str Строка.
 * @param times Количество раз.
 * @return Строка, состоящая из times строк str.
 */
char* str_repeat(char* str, size_t times);

/**
 * Ограничивает длину строки.
 * Строка будет не длиннее max_str.
 *
 * @param str Строка.
 * @param max_size Максимальный размер строки.
 */
void str_trunc(char *str, int max_len);

/**
 * Проверяет строку на отсутствие запрещенных символов.
 *
 * @param str Строка.
 * @param whitelist Разрешенные символы.
 * @return Ошибку, если строка не прошла проверку, или 0.
 */
error_t str_validate(char *str, char *whilelist);

/**
 * Показывает, является ли симпол допустимым в пути.
 *
 * @param c
 * @return Допустим или нет.
 */
int char_is_valid(char c);

#endif /* !UTILS_H_ */

