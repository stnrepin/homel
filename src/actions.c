#include "actions.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "consts.h"
#include "app-error.h"
#include "file-list.h"
#include "utils.h"
#include "db-controller.h"
#include "menu.h"
#include "menus.h"

/*
 * MAIN MENU
 */

error_t save_db_action(FileList *files, int act_index) {
    error_t err;

    save_files(files, &err);

    if (SUCC(err)) {
        printf("Files were successfully saved\n\n");
    }

    return err;
}

error_t add_file_action(FileList *files, int act_index) {
    error_t err;
    File *f;

    f = read_file_from_stdin(&err);

    if (SUCC(err)) {
        f->id = get_last_id(files) + 1;

        FileList_add(files, f);

        printf("File was successfully added\n\n");
    }

    return err;
}

error_t delete_file_action(FileList *files, int act_index) {
    error_t err;
    int id, found;
    FileListItem *cur, *prev;

    found = 0;
    id = read_id(&err);

    if (SUCC(err)) {
        prev = NULL;
        cur = files->first;
        while (!found && cur != NULL) {
            if (cur->file->id == id) {
                if (prev == NULL) {
                    files->first = cur->next;
                }
                else {
                    prev->next = cur->next;
                }
                File_destroy(cur->file);
                FileListItem_destroy(cur);

                files->count--;
                found = 1;
            }
            prev = cur;
            cur = cur->next;
        }

        if (!found) {
            printf("File with ID %d not found.\n", id);
        }
        else {
            printf("File with ID %d successfully removed\n", id);
        }
    }

    puts("");

    return err;
}

error_t edit_file_action(FileList *files, int act_index) {
    error_t err;
    File *new_f;
    int id, found;
    FileListItem *cur;

    found = 0;
    id = read_id(&err);

    if (SUCC(err)) {
        cur = files->first;
        while (!found && SUCC(err) && cur != NULL) {
            if (cur->file->id == id) {
                new_f = edit_file(cur->file, &err);
                found = 1;
                if (SUCC(err)) {
                    File_destroy(cur->file);
                    cur->file = new_f;
                }
                else {
                    File_destroy(new_f);
                }
            }
            cur = cur->next;
        }
    }

    if (SUCC(err)) {
        if (!found) {
            printf("File with ID %d not found.\n", id);
        }
        else {
            printf("File with ID %d successfully edited\n", id);
        }
    }

    return err;
}

error_t print_all_files_action(FileList *files, int act_index) {
    FileListItem *cur;

    if (files->count == 0) {
        printf("There are no files.\n");
    }
    else {
        printf("Count of files: %d\n\n", (int)files->count);

        print_table_header();

        cur = files->first;
        while (cur != NULL) {
            print_file(cur->file);
            if (cur->next != NULL) {
                print_hline();
            }

            cur = cur->next;
        }
    }

    puts("");

    return SUCCESS;
}

error_t open_find_menu_action(FileList *files, int act_index) {
    error_t err;
    Menu *find_menu;

    err = SUCCESS;
    find_menu = build_find_menu();

    if (SUCC(err)) {
        Menu_draw(find_menu);
        err = Menu_run(find_menu, files);
    }

    return err;
}

error_t open_sort_menu_action(FileList *files, int act_index) {
    error_t err;
    Menu *sort_menu;

    err = SUCCESS;
    sort_menu = build_sort_menu();

    if (SUCC(err)) {
        Menu_draw(sort_menu);
        err = Menu_run(sort_menu, files);
    }

    return err;
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
    error_t err;
    FileList *found;
    FileListItem *cur;
    int id;

    found = FileList_new();

    printf("Enter path to search: ");
    id = read_id(&err);

    cur = files->first;
    while (cur != NULL) {
        if (cur->file->id == id) {
            FileList_add(found, cur->file);
        }

        cur = cur->next;
    }

    print_all_files_action(found, -1);

    FileList_destroy(found);

    return err;
}

error_t find_file_by_tag_action(FileList *files, int act_index) {
    error_t err;
    int t, i, was_found;
    FileList *found;
    FileListItem *cur;
    char *tpath, *tpath_str;

    err = SUCCESS;
    found = FileList_new();

    printf("Enter tpath to search: ");
    tpath = read_line(&t);

    cur = files->first;
    while (cur != NULL) {
        was_found = 0;
        for (i = 0; i < cur->file->tps_count && !was_found; i++) {
            tpath_str = TagPath_to_str(cur->file->tpathes[i]);
            if (strcmp(tpath_str, tpath) == 0) {
                FileList_add(found, cur->file);
                was_found = 1;
            }
            free(tpath_str);
        }

        cur = cur->next;
    }

    print_all_files_action(found, -1);

    FileList_destroy(found);
    free(tpath);

    return err;
}

error_t find_file_by_path_action(FileList *files, int act_index) {
    error_t err;
    int t;
    FileList *found;
    FileListItem *cur;
    char *path;

    err = SUCCESS;
    found = FileList_new();

    printf("Enter path to search: ");
    path = read_line(&t);

    cur = files->first;
    while (cur != NULL) {
        if (strcmp(cur->file->rel_path, path) == 0) {
            FileList_add(found, cur->file);
        }

        cur = cur->next;
    }

    print_all_files_action(found, -1);

    FileList_destroy(found);
    free(path);

    return err;
}

/*
 * SORT MENU
 */

error_t sort_files_by_id_action(FileList *files, int act_index) {
    int i;
    File **arr;
    FileList *sorted;

    if (files->count == 0) {
        printf("There are no files.\n");
    }
    else {
        arr = FileList_to_array(files);

        qsort(arr, files->count, sizeof(File *), (int(*) (const void *, const void *))file_by_id_comparer);

        sorted = FileList_from_array(arr, files->count);
        print_all_files_action(sorted, -1);

        FileList_destroy(sorted);

        for (i = 0; i < files->count; i++) {
            File_destroy(arr[i]);
        }
        free(arr);
    }

    return SUCCESS;
}

error_t sort_files_by_path_action(FileList *files, int act_index) {
    int i;
    File **arr;
    FileList *sorted;

    if (files->count == 0) {
        printf("There are no files.\n");
    } else {
        arr = FileList_to_array(files);

        qsort(arr, files->count, sizeof(File *), (int (*)(const void *, const void *)) file_by_path_comparer);

        sorted = FileList_from_array(arr, files->count);
        print_all_files_action(sorted, -1);

        FileList_destroy(sorted);

        for (i = 0; i < files->count; i++) {
            File_destroy(arr[i]);
        }
        free(arr);
    }

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
        puts("");

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

int read_id(error_t *err) {
    int id, c;

    *err = SUCCESS;

    printf("Enter ID: ");
    if(scanf("%10d", &id) != 1) {
        *err = E_INVALID_STR;
    }

    /* Очищаем буфер ввода, оставшийся после выполнения scanf. */
    while ((c = getchar()) != '\n' && c != EOF) { }

    return id;
}

File *edit_file(File *file, error_t *err) {
    File *f;
    int i, len;
    char *tpath_str, *new_tpath_str, *new_path;

    *err = SUCCESS;
    f = File_clone(file);

    for (i = 0; i < f->tps_count && SUCC(*err); i++) {
        tpath_str = TagPath_to_str(f->tpathes[i]);

        printf("Enter new tpath #%d (default - %s): ", i+1, tpath_str);
        new_tpath_str = read_line(&len);

        free(tpath_str);

        if (len > 0) {
            *err = str_validate(new_tpath_str, "");
            if (SUCC(*err)) {
                f->tpathes[i] = TagPath_from_str(new_tpath_str);
            }
        }

        free(new_tpath_str);
    }


    printf("Enter new file path (default - %s): ", f->rel_path);
    new_path = read_line(&len);


    if (len > 0) {
        *err = str_validate(new_path, "");
        if (SUCC(*err)) {
            free(f->rel_path);
            f->rel_path = new_path;
        }
        else {
            free(new_path);
        }
    }

    return f;
}

int file_by_id_comparer(File **f1, File **f2) {
    return (*f1)->id - (*f2)->id;
}

int file_by_path_comparer(File **f1, File **f2) {
    return strcmp((*f1)->rel_path, (*f2)->rel_path);
}
