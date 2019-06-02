#include "db-controller.h"

#include <stdlib.h>
#include <string.h>

#include "sqlite3.h"

#include "app-error.h"
#include "consts.h"
#include "file.h"
#include "file-list.h"
#include "utils.h"

void load_db(error_t *err) {
    int res;

    *err = SUCCESS;

    if (db != NULL) {
        handle_fatal_error(E_DB_OPEN_TWICE);
    }

    res = sqlite3_open_v2("index.db", &db,
            SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
    if (res != SQLITE_OK) {
        handle_fatal_error(E_DB_OPEN);
    }

    create_main_table();
}

void load_db_mem(error_t *err) {
    int res;

    *err = SUCCESS;

    if (db != NULL) {
        handle_fatal_error(E_DB_OPEN_TWICE);
    }

    res = sqlite3_open(":memory:", &db);
    if (res != SQLITE_OK) {
        handle_fatal_error(E_DB_OPEN);
    }

    create_main_table();
}

void close_db() {
    sqlite3_close(db);
    db = NULL;
}

void create_main_table() {
    const char *CREATE_NEW_TABLE_SQL =
        "CREATE TABLE IF NOT EXISTS Files(Id INT, TagPathes TEXT, Path TEXT);";

    execute_sql(CREATE_NEW_TABLE_SQL);
}

void clear_main_table() {
    const char *CLEAR_TABLE_SQL =
        "DROP TABLE IF EXISTS Files;";

    execute_sql(CLEAR_TABLE_SQL);
    create_main_table();
}

void execute_sql(const char *sql) {
    int rc;
    char *err_msg;

    if (db == NULL) {
        handle_fatal_error(E_INTERNAL);
    }

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK ) {
        handle_fatal_error(E_DB_STMT_EVAL);
    }
}

FileList *load_files() {
    const char *GET_ALL_FILES_SQL =
        "SELECT * FROM Files;";

    int rc, file_id, tps_count, i;
    char *path, *tpathes_str;
    const char *err_msg;
    sqlite3_stmt *stmt;
    FileList *files;
    TagPath **tpathes;
    File *file;

    if (db == NULL) {
        handle_fatal_error(E_INTERNAL);
    }

    files = FileList_new();
    rc = sqlite3_prepare_v2(db, GET_ALL_FILES_SQL, -1, &stmt, &err_msg);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt);
        close_db();
        handle_fatal_error(E_DB_STMT_EVAL);
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        file_id = sqlite3_column_int(stmt, 0);
        tpathes_str = (char *)sqlite3_column_text(stmt, 1);
        path = (char *)sqlite3_column_text(stmt, 2);

        tpathes = get_tpathes_from_str(tpathes_str, &tps_count);
        file = File_build(file_id, tpathes, tps_count, path);

        FileList_add(files, file);

        for (i = 0; i < tps_count; i++) {
            TagPath_destroy(tpathes[i]);
        }
    }

    sqlite3_finalize(stmt);

    return files;
}

TagPath **get_tpathes_from_str(char *str, int *count) {
    char *tpath_str, **tpath_parts, *t_str;
    TagPath *tpath, **tpathes;

    int tpathes_count, tpath_count, i;

    *count = 0;

    str = strdup_(str);
    tpathes_count = strcnt_(str, ';') + 1;
    tpathes = malloc(tpathes_count * sizeof(TagPath *));
    if (tpathes == NULL) {
        handle_fatal_error(E_ALLOC);
    }

    while (str != NULL) {
        tpath_str = strsep_(&str, ";");
        tpath_count = strcnt_(tpath_str, '/') + 1;

        tpath_parts = malloc(tpath_count * sizeof(char*));
        if (tpath_parts == NULL) {
            handle_fatal_error(E_ALLOC);
        }

        i = 0;
        while ((t_str = strsep_(&tpath_str, "/")) != NULL) {
            tpath_parts[i++] = t_str;
        }

        tpath = TagPath_build(tpath_parts, tpath_count);
        tpathes[*count] = tpath;
        (*count)++;

        free(tpath_parts);
    }

    return tpathes;
}

void save_files(FileList *list, error_t *err) {
    File *f;
    FileListItem *cur;
    char *tpathes_str,
         *sql;
    const char *err_msg;
    int rc, i;
    sqlite3_stmt *stmt;

    *err = SUCCESS;

    if (db == NULL) {
        handle_fatal_error(E_INTERNAL);
    }

    clear_main_table();
    create_main_table();

    if (list->count > 0) {
        sql = create_insert_list_sql(list);

        rc = sqlite3_prepare_v2(db, sql, -1, &stmt, &err_msg);
        if (rc != SQLITE_OK) {
            handle_fatal_error(E_DB_STMT_EVAL);
        }

        i = 1; /* The leftmost SQL parameter has an index of 1. */
        cur = list->first;
        while (cur != NULL) {
            f = cur->file;
            tpathes_str = tpathes_to_str(f->tpathes, f->tps_count);

            sqlite3_bind_int(stmt, i++, f->id);
            sqlite3_bind_text(stmt, i++, tpathes_str, -1, free);
            sqlite3_bind_text(stmt, i++, f->rel_path, -1, NULL);

            cur = cur->next;
        }

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            handle_fatal_error(E_DB_STMT_EVAL);
        }

        sqlite3_finalize(stmt);
        free(sql);
    }
}

char *tpathes_to_str(TagPath **tps, int count) {
    char *tps_str;
    int tps_str_len, i, j;

    tps_str_len = 0;
    for (i = 0; i < count; i++) {
        for (j = 0; j < tps[i]->count; j++) {
            tps_str_len += strlen(tps[i]->tags[j]);
            tps_str_len += 1; /* Symbol ';'. */
        }
        tps_str_len += 1; /* Symbols '/' and '\0'. */
    }

    tps_str = malloc(tps_str_len * sizeof(char));
    if (tps_str == NULL) {
        handle_fatal_error(E_ALLOC);
    }
    tps_str[0] = '\0';

    for (i = 0; i < count; i++) {
        for (j = 0; j < tps[i]->count; j++) {
            strcat(tps_str, tps[i]->tags[j]);
            if (j != tps[i]->count - 1) {
                strcat(tps_str, ";");
            }
        }

        if (i != count - 1) {
            strcat(tps_str, "/");
        }
    }

    return tps_str;
}

char *create_insert_list_sql(FileList *list) {

    const char *INSERT_FILES_SQL_TEMPLATE = 
        "INSERT INTO Files (Id, TagPathes, Path) VALUES ";

    char *values, *sql;
    int values_len, sql_len;

    values = str_repeat("(?, ?, ?), ", list->count);
    values_len = strlen(values);
    if (values_len > 1) {
        values[values_len-2] = ';';
    }

    sql_len = strlen(INSERT_FILES_SQL_TEMPLATE) + strlen(values) + 1;
    sql = malloc(sql_len * sizeof(char));
    if (sql == NULL) {
        handle_fatal_error(E_ALLOC);
    }
    sql[0] = '\0';

    strcat(sql, INSERT_FILES_SQL_TEMPLATE);
    strcat(sql, values);

    return sql;
}

