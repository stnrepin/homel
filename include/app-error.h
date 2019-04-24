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
