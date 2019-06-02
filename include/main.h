#ifndef MAIN_H_
#define MAIN_H_

#include "app-error.h"
#include "file-list.h"

/**
 * Точка входа.
 *
 * @param argc Количество параметром командной строки.
 * @param argv Параметры командной строки.
 * @return int Результат.
 */
int main(int argc, char **argv);

/**
 * Выводит на экран информацию о версии программы.
 */
void print_version();

/**
 * Загружает файлы из индекса.
 * Если индекс не существует, то он будет создан.
 *
 * @param err Хранит код ошибки.
 * @return Загруженный список планет.
 */
FileList *load_files_from_db(error_t *err);

#endif /* !MAIN_H_ */

