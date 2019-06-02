#ifndef DB_CONTROLLER_H_
#define DB_CONTROLLER_H_

#include "sqlite3.h"

#include "app-error.h"
#include "file.h"
#include "file-list.h"

/*
 * Make db visible for tests.
 */
#if UNIT_TEST

sqlite3 *db;

#else

/**
 * Дескриптор БД.
 */
static sqlite3 *db;

#endif /* BUILD_TEST */

/**
 * Загружает БД.
 *
 * @param err Код ошибки.
 */
void load_db(error_t *err);

/**
 * Загружает БД из памяти.
 *
 * @param err Код ошибки.
 */
void load_db_mem(error_t *err);

/**
 * Освобождает БД.
 */
void close_db();

/*
 * Создает главную таблицу.
 */
void create_main_table();

/*
 * Очищает главную таблицу.
 */
void clear_main_table();

/*
 * Выполняет sql-запрос.
 *
 * @param sql Запрос.
 */
void execute_sql(const char *sql);

/*
 * Загружает файлы из БД.
 *
 * @return Список файлов.
 */
FileList *load_files();

/**
 * Парсит массив TagPath из строки.
 *
 * @patam str Строка.
 * @param count Число TagPath в строке.
 * @return Массив TagPath.
 */
TagPath **get_tpathes_from_str(char *str, int *count);

/**
 * Сохраняет список в индекс.
 *
 * @param files Список файлов.
 * @param err Код ошибки.
 */
void save_files(FileList *list, error_t *err);

/**
 * Преобразует массив TagPath в строку.
 *
 * @param tps Массив TagPath.
 * @param count Количество TagPath в массиве.
 * @return Строковое предстваление массива TagPath.
 */
char *tpathes_to_str(TagPath **tps, int count);

/**
 * Формирует запрос к БД для добавление элементов списка.
 *
 * @param list Список файлов.
 * @return SQL-запрос.
 */
char *create_insert_list_sql(FileList *list);

#endif /* !DB_CONTROLLER_H_ */

