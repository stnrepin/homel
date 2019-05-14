#include "unity.h"

#include "file.h"
#include "test-utils.h"

TagPath *create_simple_tpath1() {
    return TagPath_build(BUILD_ARR(char *, 3, "abc", "", "55 555"), 3);
}

TagPath *create_empty_tpath() {
    return TagPath_build(BUILD_ARR(char *, 0, ""), 0);
}

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

/*
 * Method: TagPath_new.
 */
void should_create_tpath_with_empty_fields() {
    TagPath *tp;

    tp = TagPath_new();

    TEST_ASSERT_EQUAL(0, tp->count);
    TEST_ASSERT_NULL(tp->tags);

    TagPath_destroy(tp);
}

/*
 * Method: TagPath_build.
 */
void should_create_tpath_with_valid_values_and_destroy() {
    TagPath *tp;

    tp = create_simple_tpath1();

    TEST_ASSERT_EQUAL(3, tp->count);
    TEST_ASSERT_EQUAL_STRING("abc", tp->tags[0]);
    TEST_ASSERT_EQUAL_STRING("", tp->tags[1]);
    TEST_ASSERT_EQUAL_STRING("55 555", tp->tags[2]);

    TagPath_destroy(tp);
}

/*
 * Method: TagPath_build.
 */
void should_create_empty_tpath_with_valid_values_and_destroy() {
    TagPath *tp;

    tp = create_empty_tpath();

    TEST_ASSERT_EQUAL(0, tp->count);
    TEST_ASSERT_NULL(tp->tags);

    TagPath_destroy(tp);
}

/*
 * Method: TagPath_clone.
 */
void should_create_full_clone_of_path() {
    TagPath *tp1, *tp2;

    tp1 = create_simple_tpath1();
    tp2 = TagPath_clone(tp1);

    TEST_ASSERT_EQUAL(tp1->count, tp2->count);
    TEST_ASSERT_EQUAL_STRING_ARRAY(tp1->tags, tp2->tags, tp1->count);
    /* Tags in tp2 should be a copy of tags in tp1. */
    TEST_ASSERT_NOT_EQUAL(tp1->tags, tp2->tags);
    TEST_ASSERT_NOT_EQUAL(tp1->tags[0], tp2->tags[0]);
    TEST_ASSERT_NOT_EQUAL(tp1->tags[1], tp2->tags[1]);
    TEST_ASSERT_NOT_EQUAL(tp1->tags[2], tp2->tags[2]);

    TagPath_destroy(tp1);
    TagPath_destroy(tp2);
}

/*
 * Method: TagPath_clone.
 */
void should_create_full_clone_of_null_path() {
    TagPath *tp1, *tp2;


    tp1 = NULL;
    tp2 = TagPath_clone(tp1);

    TEST_ASSERT_NULL(tp2);

    TagPath_destroy(tp1);
    TagPath_destroy(tp2);
}

/*
 * Method: File_new.
 */
void should_create_file_with_empty_fields() {
    File *f;
    f = File_new();

    TEST_ASSERT_EQUAL(-1, f->id);
    TEST_ASSERT_EQUAL(0, f->tps_count);
    TEST_ASSERT_NULL(f->rel_path);
    TEST_ASSERT_NULL(f->tpathes);

    File_destroy(f);
}

/*
 * Method: File_build.
 */
void should_create_file_with_valid_values_and_destroy() {
    File *f;

    f = create_simple_file1();

    TEST_ASSERT_EQUAL(0, f->id);
    TEST_ASSERT_EQUAL_STRING("simple/file/1", f->rel_path);
    TEST_ASSERT_EQUAL(3, f->tps_count);
    TEST_ASSERT_NOT_NULL(f->tpathes);
    TEST_ASSERT_EQUAL(3, f->tpathes[0]->count);
    TEST_ASSERT_EQUAL(1, f->tpathes[1]->count);
    TEST_ASSERT_EQUAL(0, f->tpathes[2]->count);
    TEST_ASSERT_EQUAL_STRING("cc", f->tpathes[0]->tags[2]);

    File_destroy(f);
}

/*
 * Method: File_build.
 */
void should_create_file_without_tags_with_valid_values_and_destroy() {
    File *f;

    f = create_file_without_tags();

    TEST_ASSERT_EQUAL(1, f->id);
    TEST_ASSERT_EQUAL_STRING("no-tag-file", f->rel_path);
    TEST_ASSERT_EQUAL(0, f->tps_count);
    TEST_ASSERT_NULL(f->tpathes);

    File_destroy(f);
}

/*
 * Method: File_equals.
 */
void should_right_compare_file_by_id() {
    File *f1, *f2;

    f1 = create_simple_file1();
    f2 = create_file_without_tags();
    f1->id = f2->id = 9;

    TEST_ASSERT(File_equals(f1, f2));

    f1->id = 1;
    TEST_ASSERT_FALSE(File_equals(f1, f2));


    File_destroy(f1);
    File_destroy(f2);
}

/*
 * Method: File_equals.
 */
void should_right_compare_file_by_ptr() {
    File *f;

    f = create_simple_file1();

    TEST_ASSERT(File_equals(f, f));

    File_destroy(f);
}

/*
 * Method: File_equals.
 */
void should_return_false_on_comparison_of_file_with_null() {
    File *f;

    f = create_simple_file1();

    TEST_ASSERT_FALSE(File_equals(f, NULL));
    TEST_ASSERT_FALSE(File_equals(NULL, f));

    File_destroy(f);
}

/*
 * Method: File_equals.
 */
void should_return_true_on_null_files_comparison() {
    TEST_ASSERT(File_equals(NULL, NULL));
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(should_create_tpath_with_empty_fields);

    RUN_TEST(should_create_tpath_with_valid_values_and_destroy);
    RUN_TEST(should_create_empty_tpath_with_valid_values_and_destroy);

    RUN_TEST(should_create_full_clone_of_path);
    RUN_TEST(should_create_full_clone_of_null_path);

    RUN_TEST(should_create_file_with_empty_fields);

    RUN_TEST(should_create_file_with_valid_values_and_destroy);
    RUN_TEST(should_create_file_without_tags_with_valid_values_and_destroy);

    RUN_TEST(should_right_compare_file_by_id);
    RUN_TEST(should_right_compare_file_by_ptr);
    RUN_TEST(should_return_false_on_comparison_of_file_with_null);
    RUN_TEST(should_return_true_on_null_files_comparison);

    return UNITY_END();
}

