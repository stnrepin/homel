#include "actions.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "consts.h"
#include "app-error.h"
#include "file-list.h"
#include "utils.h"

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
    error_t err;
    File *f;

    f = read_file_from_stdin(&err);

    if (SUCC(err)) {
        f->id = get_last_id(files) + 1;

        FileList_add(files, f);
    }

    return err;
}

error_t delete_file_action(FileList *files, int act_index) {
    return SUCCESS;
}

error_t edit_file_action(FileList *files, int act_index) {
    return SUCCESS;
}

error_t print_all_files_action(FileList *files, int act_index) {
    FileListItem *cur;

    if (files->count == 0) {
        printf("There are no files.\n");
    }
    else {
        print_table_header();

        cur = files->first;
        while (cur != NULL) {
            print_file(cur->file);
            if (cur->next != NULL) {
                print_hline();
            }

            cur = cur->next;
        }

        puts("");
    }

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

/*
 * HELPERS
 */

void print_table_header() {
    print_row("Id", "Tags", "Path");
    print_hline();
}

void print_row(char *id_str, char *tpath, char *path) {
    int rpad, lpad, id_str_l, tpath_l, path_l;

    str_trunc(id_str, PRINT_TABLE_FIRST_COL_SIZE);
    str_trunc(tpath, PRINT_TABLE_SECOND_COL_SIZE);
    str_trunc(path, PRINT_TABLE_THIRD_COL_SIZE);

    id_str_l = strlen(id_str);
    tpath_l = strlen(tpath);
    path_l = strlen(path);

    lpad = (PRINT_TABLE_FIRST_COL_SIZE - id_str_l) / 2 + 1;
    rpad = PRINT_TABLE_FIRST_COL_SIZE - lpad - id_str_l + 2;
    printf("%*s%s%*s", lpad, "", id_str, rpad, "");

    putchar('|');

    lpad = (PRINT_TABLE_SECOND_COL_SIZE - tpath_l) / 2 + 1;
    rpad = PRINT_TABLE_SECOND_COL_SIZE - lpad - tpath_l + 2;
    printf("%*s%s%*s", lpad, "", tpath, rpad, "");

    putchar('|');

    lpad = (PRINT_TABLE_THIRD_COL_SIZE - path_l) / 2 + 1;
    rpad = PRINT_TABLE_THIRD_COL_SIZE - lpad - path_l + 2;
    printf("%*s%s%*s", lpad, "", path, rpad, "");

    putchar('\n');
}

void print_hline() {
    int i;

    for (i = 0; i < PRINT_TABLE_FIRST_COL_SIZE + 2; i++) {
        putchar('-');
    }
    putchar('|');
    for (i = 0; i < PRINT_TABLE_SECOND_COL_SIZE+ 2; i++) {
        putchar('-');
    }
    putchar('|');
    for (i = 0; i < PRINT_TABLE_THIRD_COL_SIZE+ 2; i++) {
        putchar('-');
    }
    putchar('\n');
}

void print_file(File* f) {
    int i;
    char id_str[12],
         *tpath_str;

    sprintf(id_str, "%d", f->id);

    tpath_str = f->tps_count > 0 ? TagPath_to_str(f->tpathes[0]) : "";
    print_row(id_str, tpath_str, f->rel_path);
    free(tpath_str);

    for (i = 1; i < f->tps_count; i++) {
        tpath_str = TagPath_to_str(f->tpathes[i]);
        print_row("", tpath_str, "");
        free(tpath_str);
    }
}

File *read_file_from_stdin(error_t *err) {
    File *f;
    int tps_count, t;
    char *tpath, *path;
    TagPath **tpathes;

    *err = SUCCESS;
    f = NULL;

    tpathes = malloc(READ_TPATHES_MAX_COUNT * sizeof(TagPath *));
    if (tpathes == NULL) {
        handle_fatal_error(E_ALLOC);
    }

    printf("Enter tpathes (enter empty string to finish input):\n");
    tps_count = 0;
    tpath = read_line(&t);
    while (t > 0 && SUCC(*err)) {
        if (tps_count > READ_TPATHES_MAX_COUNT) {
            *err = E_LIMIT_EXCEEDED;
        }
        else {
            *err = str_validate(tpath, "");
            tpathes[tps_count] = TagPath_from_str(tpath);
            tps_count++;
        }
        tpath = read_line(&t);
    }

    if (SUCC(*err)) {
        printf("Enter path: ");
        path = read_line(&t);

        *err = str_validate(path, "");
        if (SUCC(*err)) {
            f = File_build(-1, tpathes, tps_count, path);
        }
    }

    return f;
}

int get_last_id(FileList *fs) {
    int id;
    FileListItem *cur;

    id = -1;
    cur = fs->first;
    while (cur != NULL) {
        if (cur->next == NULL) {
            id = cur->file->id;
        }
        cur = cur->next;
    }

    return id;
}
