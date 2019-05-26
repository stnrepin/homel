#include "menu.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "app-error.h"

MenuItem *MenuItem_new() {
    MenuItem *item;

    item = malloc(sizeof(MenuItem));
    if (item == NULL) {
        handle_fatal_error(E_ALLOC);
    }

    return item;
}

void MenuItem_destroy(MenuItem *menu_item) {
    free(menu_item);
}

MenuItem *MenuItem_copy(MenuItem *src) {
    MenuItem *dest;

    dest = MenuItem_new();
    memcpy(dest, src, sizeof(MenuItem));

    return dest;
}

Menu *Menu_new() {
    Menu *menu;

    menu = malloc(sizeof(Menu));
    if (menu == NULL) {
        handle_fatal_error(E_ALLOC);
    }

    menu->count = 0;

    return menu;
}

void Menu_destroy(Menu *menu) {
    if (menu != NULL) {
        Menu_destroy_items(menu);
        menu->count = 0;
        free(menu);
    }
}

void Menu_destroy_items(Menu *menu) {
    int i;
    if (menu->items != NULL) {
        for (i = 0; i < menu->count; i++) {
            MenuItem_destroy(menu->items[i]);
        }
        free(menu->items);
    }
}

Menu *Menu_build(char *caption, MenuItem *items, int count) {
    int i;
    Menu *m;

    m = Menu_new();

    m->items = malloc(count * sizeof(MenuItem));
    if (m->items == NULL) {
        handle_fatal_error(E_ALLOC);
    }
    else {
        for (i = 0; i < count; i++) {
            m->items[i] = MenuItem_copy(&items[i]);
        }
        strcpy(m->caption, caption);
        m->count = i;
    }

    return m;
}

void Menu_draw(Menu *menu) {
    int i;
    printf("%s\n", menu->caption);
    for (i = 0; i < menu->count; i++) {
        printf("%d - %s\n", i+1, menu->items[i]->caption);
    }
}

error_t Menu_run(Menu *menu, MenuGlobalObject *planets) {
    error_t err;
    int right_input, item, c;

    do {
        printf("[%d-%d]> ", 1, menu->count);
        scanf("%d", &item);
        /* Очищаем буфер ввода, оставшийся после выполнения scanf. */
        while ((c = getchar()) != '\n' && c != EOF) { }

        right_input = (item >= 1 && item <= menu->count);

    } while (!right_input);

    puts("");
    item--;
    err = menu->items[item]->action(planets, item);

    return err;
}

