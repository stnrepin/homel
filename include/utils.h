#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include <wchar.h>

/**
 * Обертка над read_line(FILE *f) для чтения из stdin.
 * 
 * @return wchar_t* Строка.
 */
wchar_t *read_line();

/**
 * Читает строку произвольного размера из файла.
 * 
 * @param f Файл.
 * @return wchar_t* Строка.
 */
wchar_t *read_line(FILE *f);

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
 * @return Строка, состаящая из times строк str.
 */
char* str_repeat(char* str, size_t times);

#endif /* !UTILS_H_ */
