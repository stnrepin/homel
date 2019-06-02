#include "main.h"

#include <stdio.h>
#include <stdlib.h>

#include "app-error.h"
#include "consts.h"
#include "menu.h"
#include "menus.h"
#include "db-controller.h"

void print_version() {
    printf("homel v"HOMEL_VERSION"\n");
}

int main(int argc, char **argv) {
    error_t err;
    FileList *files;
    Menu *main_menu;

    main_menu = build_main_menu();

    files = load_files_from_db(&err);

    if (FAIL(err)) {
        handle_fatal_error(err);
    }

    while (err != E_SYSTEMEXIT) {
        Menu_draw(main_menu);
        err = Menu_run(main_menu, files);

        if (FAIL(err) && err != E_SYSTEMEXIT) {
            handle_error(err);
        }
    }

    close_db();
    FileList_destroy(files);

    return EXIT_SUCCESS;
}

FileList *load_files_from_db(error_t *err) {
    FileList *files;

    load_db(err);
    files = load_files();

    return files;
}

