#include "unity.h"
#include "sqlite3.h"

#include "db-controller.h"
#include "app-error.h"
#include "file.h"

#include "test-utils.h"

extern sqlite3 *db;

File *create_simple_file1() {
    TagPath *f_tps[3] = {
        TagPath_build(BUILD_ARR(char *, 3, "a", "bb", "cc"), 3),
        TagPath_build(BUILD_ARR(char *, 1, "asd asd a12"), 1),
        TagPath_build(BUILD_ARR(char *, 0, ""), 0),
    };
    return File_build(0, f_tps, 3, "simple/file/1");
}

File *create_file_without_tags() {
    return File_build(1, NULL, 0, "no-tag-file");
}

File *create_simple_file2() {
    TagPath *f_tps[1] = {
        TagPath_build(BUILD_ARR(char *, 1, "123a"), 1),
    };
    return File_build(2, f_tps, 1, "simple/file/2");
}

File **create_simple_file_array1(int *count) {
    File **files;

    *count = 3;
    files = BUILD_ARR(File *, *count,
                create_simple_file1(),
                create_file_without_tags(),
                create_simple_file2());

    return files;
}

FileList *create_simple_filelist1() {
    int count;
    File **arr = create_simple_file_array1(&count);
    return FileList_from_array(arr, count);
}

FileList *create_empty_filelist() {
    return FileList_from_array(NULL, 0);
}

/*
 * Method: load_db_mem
 */
void should_open_db_in_memory() {
    error_t err;

    load_db_mem(&err);

    TEST_ASSERT_TRUE(SUCC(err));
    TEST_ASSERT_NOT_NULL(db);

    close_db(db);

    TEST_ASSERT_NULL(db);
}

/*
 * Method: load_files & save_files
 */
void should_save_and_load_files() {
    error_t err;
    int i;
    FileList *list1 = create_simple_filelist1(),
             *list2;
    FileListItem *cur1, *cur2;

    load_db_mem(&err);
    TEST_ASSERT_TRUE(SUCC(err));

    save_files(list1, &err);
    TEST_ASSERT_TRUE(SUCC(err));

    list2 = load_files();

    TEST_ASSERT_EQUAL(list1->count, list2->count);

    cur1 = list1->first;
    cur2 = list2->first;
    i = 0;
    while (cur1 != NULL && cur2 != NULL) {
        TEST_ASSERT_NOT_EQUAL(cur1, cur2);
        TEST_ASSERT_TRUE(File_equals(cur1->file, cur2->file));

        i++;
        cur1 = cur1->next;
        cur2 = cur2->next;
    }

    TEST_ASSERT_EQUAL(list1->count, i);

    close_db(db);
}

/*
 * Method: get_tpathes_from_str
 */
void should_parse_tpathes_from_string() {
    int tp1_c, tp2_c, tp3_c;
    TagPath **tp1 = get_tpathes_from_str("", &tp1_c),
            **tp2 = get_tpathes_from_str("asd", &tp2_c),
            **tp3 = get_tpathes_from_str("aaaaa/bbb/c/1;c3;5/1", &tp3_c);

    TEST_ASSERT_EQUAL(1, tp1_c);
    TEST_ASSERT_EQUAL(1, tp2_c);
    TEST_ASSERT_EQUAL(3, tp3_c);

    TEST_ASSERT_EQUAL(1, tp1[0]->count);
    TEST_ASSERT_EQUAL_STRING("", tp1[0]->tags[0]);

    TEST_ASSERT_EQUAL(1, tp2[0]->count);
    TEST_ASSERT_EQUAL_STRING("asd", tp2[0]->tags[0]);

    TEST_ASSERT_EQUAL(4, tp3[0]->count);
    TEST_ASSERT_EQUAL_STRING("aaaaa", tp3[0]->tags[0]);
    TEST_ASSERT_EQUAL_STRING("bbb", tp3[0]->tags[1]);
    TEST_ASSERT_EQUAL_STRING("c", tp3[0]->tags[2]);
    TEST_ASSERT_EQUAL_STRING("1", tp3[0]->tags[3]);

    TEST_ASSERT_EQUAL(1, tp3[1]->count);
    TEST_ASSERT_EQUAL_STRING("c3", tp3[1]->tags[0]);

    TEST_ASSERT_EQUAL(2, tp3[2]->count);
    TEST_ASSERT_EQUAL_STRING("5", tp3[2]->tags[0]);
    TEST_ASSERT_EQUAL_STRING("1", tp3[2]->tags[1]);
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(should_open_db_in_memory);
    RUN_TEST(should_parse_tpathes_from_string);
    RUN_TEST(should_save_and_load_files);

    return UNITY_END();
}

