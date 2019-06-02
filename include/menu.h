#ifndef MENU_H_
#define MENU_H_

#include <stddef.h>

#include "consts.h"
#include "file-list.h"
#include "app-error.h"

typedef FileList MenuGlobalObject;
typedef error_t (*ActionFunc) (MenuGlobalObject*, int);

/**
 * Объект, представляющий элемент меню.
 */
typedef struct {
    char caption[MAX_STRING_LEN];
    ActionFunc action;
} MenuItem;

/**
 * Объект, представляющий меню (список элементов меню).
 */
typedef struct {
    char caption[MAX_STRING_LEN];
    MenuItem **items;
    int count;
} Menu;

/**
 * Создает новый объект MenuItem (для caption память не выделяется).
 *
 * @return MenuItem* Созданный объект.
 */
MenuItem *MenuItem_new();

/**
 * Уничтожает объект MenuItem (память освобождается только из-под menu_item).
 *
 * @param menu_item Объект для уничтожения.
 */
void MenuItem_destroy(MenuItem *menu_item);

/**
 * Копирует данный объект в целевой (память должна быть заранее выделена).
 *
 * @param src  Исходный объект.
 * @return MenuItem* Копия объекта.
 */
MenuItem *MenuItem_copy(MenuItem *src);

/**
 * Создает новый объект Menu (для items и caption
 * память не выделяется). Поле count обнуляется.
 *
 * @return Menu* Созданный объект.
 */
Menu *Menu_new();

/**
 * Уничтожает объект Menu (освобождает память только из-под Menu и items, вызывая
 * Menu_destroy_items).
 *
 * @param menu Объект для уничтожения.
 */
void Menu_destroy(Menu *menu);

/**
 * Уничтожает items в меню (вызывая MenuItem_destroy).
 *
 * @param menu Меню.
 */
void Menu_destroy_items(Menu *menu);

/**
 * Создает новый объект Menu и копирует в него items.
 *
 * Копии items[i].caption и items[i].action не делаются (т.е. они будут
 * указывать на ту же память, что и исходные в items).
 *
 * @param caption Заголовок меню.
 * @param items Элементы меню.
 * @param count Число items.
 * @return Menu* Созданный и заполненный объект.
 */
Menu *Menu_build(char *caption, MenuItem *items, int count);

/**
 * Выводит на экран Меню (вместе с пунктами).
 *
 * @param menu Меню.
 */
void Menu_draw(Menu *menu);

/**
 * Спрашивает у пользователя о том, какой пункт требуется выполнить и вызывает
 * для него action.
 *
 * @param menu Меню.
 * @param obj Объект, который будет передан в action.
 * @return error_t Возвращает 0 при удаче, иначе - код ошибки.
 */
error_t Menu_run(Menu *menu, MenuGlobalObject *obj);

#endif /* !MENU_H_ */

