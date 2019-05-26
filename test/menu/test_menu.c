#include <stdio.h>

#include "unity.h"

#include "menu.h"
#include "file-list.h"

error_t menu_action1(FileList *files, int index) {
    printf("1");
    return SUCCESS;
}

error_t menu_action2(FileList *files, int index) {
    printf("2");
    return SUCCESS;
}

error_t menu_action3(FileList *files, int index) {
    printf("3");
    return SUCCESS;
}

void should_create_valid_copy_of_menu_item() {
    MenuItem *mi_c,
              mi_src  = { "abcd 123", menu_action1 };

    mi_c = MenuItem_copy(&mi_src);

    TEST_ASSERT_EQUAL_STRING(mi_src.caption, mi_c->caption);
    TEST_ASSERT_EQUAL_PTR(mi_src.action, mi_c->action);
}

void should_create_menu_with_empty_fields() {
    Menu *m;

    m = Menu_new();

    TEST_ASSERT_EQUAL(0, m->count);
}

void should_build_valid_menu() {
    size_t i;
    Menu *m;
    MenuItem items[3] =
    {
        { "menu item 1", menu_action1 },
        { "", menu_action2 },
        { "123", menu_action3 },
    };


    m = Menu_build("menu cap", items, 3);

    TEST_ASSERT_EQUAL_STRING("menu cap", m->caption);
    TEST_ASSERT_EQUAL(3, m->count);

    for (i  = 0; i < m->count; i++) {
        TEST_ASSERT_NOT_EQUAL(&items[i], m->items[0]);
        TEST_ASSERT_EQUAL_STRING(items[i].caption, m->items[i]->caption);
        TEST_ASSERT_EQUAL_PTR(items[i].action, m->items[i]->action);
    }
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(should_create_valid_copy_of_menu_item);
    RUN_TEST(should_create_menu_with_empty_fields);
    RUN_TEST(should_build_valid_menu);

    return UNITY_END();
}

