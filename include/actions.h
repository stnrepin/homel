#ifndef ACTIONS_H_
#define ACTIONS_H_

#include "app-error.h"
#include "file-list.h"

/*
 * MAIN MENU
 */

error_t help_action(FileList *files, int act_index);

error_t quit_action(FileList *files, int act_index);

error_t save_db_action(FileList *files, int act_index);

error_t add_file_action(FileList *files, int act_index);

error_t delete_file_action(FileList *files, int act_index);

error_t edit_file_action(FileList *files, int act_index);

error_t print_all_files_action(FileList *files, int act_index);

error_t open_find_menu_action(FileList *files, int act_index);

error_t clear_screen_action(FileList *files, int act_index);

error_t quit_action(FileList *files, int act_index);

/*
 * FIND MENU
 */

error_t find_file_by_id_action(FileList *files, int act_index);

error_t find_file_by_tag_action(FileList *files, int act_index);

error_t find_file_by_path_action(FileList *files, int act_index);

/*
 * HELPERS
 */

/**
 * Выводит на экран заголовок таблицы.
 */
void print_table_header();

/**
 * Выводит на экран одну строку таблицы.
 *
 * @param id_str ID файла.
 * @param tpath TagPath (строка, разделенная '/').
 * @param path Относительный путь до файла.
 */
void print_row(char *id_str, char *tpath, char *path);

/**
 * Выводит на экран горизонтальную линию-разделитель.
 */
void print_hline();

/**
 * Выводит на экран информацию о файле.
 *
 * @param f Файл.
 */
void print_file(File *f);

/**
 * Читает с файл из stdin.
 *
 * @param err Ошибка.
 */
File *read_file_from_stdin(error_t *err);

/**
 * Возвращает ID последнего файла в списке (или -1, если файлов нет).
 *
 * @param fs Список файлов.
 * @return ID последнего файла.
 */
int get_last_id(FileList *fs);

#endif /* !ACTIONS_H_ */

