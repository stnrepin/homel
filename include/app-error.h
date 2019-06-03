/* 'ERR' due to idiotical highlighting in VSCode. */
#ifndef APP_ERR_H_
#define APP_ERR_H_

#define SUCCESS (error_t)0
#define FAIL(e) (e != SUCCESS)
#define SUCC(e) (e == SUCCESS)

/**
 * Представляет код ошибок.
 * 
 * 0 означает отсутствие ошибки.
 * 
 */
typedef enum {
    E_ALLOC = 1,                /*< Ошибка выделения памяти. */
    E_SYSTEMEXIT = 2,           /*< Обозначает необходимость завершения роботы
                                    программы */
    E_INTERNAL = 3,             /*< Внутренняя ошибка в программе. */

    E_DB_OPEN_TWICE = 4,        /*< Попытка повторного открытия БД. */
    E_DB_OPEN = 5,              /*< Ошибка при открытии БД. */
    E_DB_STMT_EVAL = 6,         /*< Ошибка при выполнении запроса к БД. */

    E_LIMIT_EXCEEDED = 7,       /*< Указывает на достижение некоторого лимита */
    E_INVALID_STR = 8,          /*< Указывает на то, что введена некорректная строка */

} error_t;

/**
 * Обрабатывает ошибку.
 * 
 * @param err Код ошибки.
 */
void handle_error(error_t err);

/**
 * Обрабатывает критическую ошибку.
 * 
 * @param err Код ошибки.
 */
void handle_fatal_error(error_t err);

/**
 * Возвращает строковое описание ошибки.
 * 
 * @param err Код ошибки.
 * @return char* Описание ошибки.
 */
char *get_message_by_code(error_t err);

#endif /* !APP_ERR_H_ */
