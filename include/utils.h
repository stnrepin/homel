#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>

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

#endif /* !UTILS_H_ */
