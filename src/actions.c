#include "actions.h"

#include <stdlib.h>
#include <stdio.h>

#include "app-error.h"
#include "file-list.h"

/*
 * MAIN MENU
 */

error_t help_action(FileList *files, int act_index) {
    return SUCCESS;
}

error_t load_db_action(FileList *files, int act_index) {
    return SUCCESS;
}

error_t save_db_action(FileList *files, int act_index) {
    return SUCCESS;
}

error_t add_file_action(FileList *files, int act_index) {
    return SUCCESS;
}

error_t delete_file_action(FileList *files, int act_index) {
    return SUCCESS;
}

error_t edit_file_action(FileList *files, int act_index) {
    return SUCCESS;
}

error_t print_all_files_action(FileList *files, int act_index) {
    return SUCCESS;
}

error_t open_find_menu_action(FileList *files, int act_index) {
    return SUCCESS;
}

error_t clear_screen_action(FileList *files, int act_index) {
    system("@cls||clear");
    return SUCCESS;
}

error_t quit_action(FileList *files, int act_index) {
    return E_SYSTEMEXIT;
}

/*
 * FIND MENU
 */

error_t find_file_by_id_action(FileList *files, int act_index) {
    return SUCCESS;
}

error_t find_file_by_tag_action(FileList *files, int act_index) {
    return SUCCESS;
}

error_t find_file_by_path_action(FileList *files, int act_index) {
    return SUCCESS;
}

