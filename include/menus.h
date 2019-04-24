#ifndef MENUS_H_
#define MENUS_H_

#include "menu.h"

/**
 * Создает главное меню.
 * 
 * @return Menu* Главное меню
 */
Menu *create_main_menu();

/**
 * Создает меню поиска (выбор поля по которому производится поиск).
 * 
 * @return Menu* Меню поиска.
 */
Menu *create_search_menu();

/**
 * Создает меню просмотра (сортировки).
 * 
 * @return Menu* Меню просмотра.
 */
Menu *create_view_menu();

#endif /* !MENUS_H_ */
