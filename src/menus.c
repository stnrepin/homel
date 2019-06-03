#include "menus.h"

#include "menu.h"
#include "actions.h"

#define MAIN_MENU_ITEMS { \
    MENU_ITEM("Save", save_db_action), \
    MENU_ITEM("Add", add_file_action), \
    MENU_ITEM("Edit", edit_file_action), \
    MENU_ITEM("Delete", delete_file_action), \
    MENU_ITEM("Print", print_all_files_action), \
    MENU_ITEM("Find", open_find_menu_action), \
    MENU_ITEM("Clear screen", clear_screen_action), \
    MENU_ITEM("Quit", quit_action) \
}
MENU_BUILDER(main, MAIN_MENU_ITEMS)

#define FIND_MENU_ITEMS { \
    MENU_ITEM("By ID", find_file_by_id_action), \
    MENU_ITEM("By tag", find_file_by_tag_action), \
    MENU_ITEM("By file path", find_file_by_path_action), \
}
MENU_BUILDER(find, FIND_MENU_ITEMS);

