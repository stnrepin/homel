#ifndef MENUS_H_
#define MENUS_H_

#include "menu.h"

#define MENU_ITEM(title, func) { title, func }

#define MENU_BUILDER(name, items) \
    Menu *build_##name##_menu() { \
        int items_count; \
        MenuItem menu_items[] = items; \
        items_count = sizeof(menu_items)/sizeof(menu_items[0]); \
        return Menu_build("Choose action:", menu_items, items_count); \
    }

/**
 * Создает главное меню.
 *
 * @return Menu* Главное меню
 */
Menu *build_main_menu();

/**
 * Создает меню поиска (выбор поля по которому производится поиск).
 *
 * @return Menu* Меню поиска.
 */
Menu *build_search_menu();

/**
 * Создает меню просмотра (сортировки).
 *
 * @return Menu* Меню просмотра.
 */
Menu *build_view_menu();

#endif /* !MENUS_H_ */

