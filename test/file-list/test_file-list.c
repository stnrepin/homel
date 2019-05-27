#include "unity.h"

#include "file.h"
#include "file-list.h"
#include "test-utils.h"

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

FileList *create_empty_filelist() {
    return FileList_from_array(NULL, 0);
}

/*
 * Method: FileList_from_array
 */
void should_build_valid_list_from_array() {
    int files_count;
    File **files;
    FileList *l;

    files = create_simple_file_array1(&files_count);
    l = FileList_from_array(files, files_count);

    TEST_ASSERT_EQUAL(files_count, l->count);

    TEST_ASSERT_NOT_EQUAL(files[0], l->first->file);
    TEST_ASSERT_NOT_EQUAL(files[1], l->first->next->file);
    TEST_ASSERT_NOT_EQUAL(files[2], l->first->next->next->file);
    TEST_ASSERT_NULL(l->first->next->next->next);

    TEST_ASSERT_TRUE(File_equals(files[0], l->first->file));
    TEST_ASSERT_TRUE(File_equals(files[1], l->first->next->file));
    TEST_ASSERT_TRUE(File_equals(files[2], l->first->next->next->file));
}

/*
 * Method: FileList_from_array
 */
void should_build_valid_empty_list_from_array() {
    FileList *l;

    l = create_empty_filelist();

    TEST_ASSERT_EQUAL(0, l->count);
    TEST_ASSERT_NULL(l->first);
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(should_build_valid_list_from_array);
    RUN_TEST(should_build_valid_empty_list_from_array);

    return UNITY_END();
}
