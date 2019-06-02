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

#endif /* !ACTIONS_H_ */

