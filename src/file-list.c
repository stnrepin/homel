#include "file-list.h"

#include <stdlib.h>

#include "app-error.h"
#include "file.h"

FileListItem *FileListItem_new() {
    FileListItem *item;
    item = malloc(sizeof(FileListItem));
    if (item == NULL) {
        handle_fatal_error(E_ALLOC);
    }

    item->file = NULL;
    item->next = NULL;

    return item;
}

void FileListItem_destroy(FileListItem *item) {
    free(item);
}

FileList *FileList_new() {
    FileList *list;

    list = malloc(sizeof(FileList));
    if (list == NULL) {
        handle_fatal_error(E_ALLOC);
    }
	list->first = NULL;
    list->count = 0;

    return list;
}

void FileList_destroy(FileList *list) {
    FileListItem *cur, *next;

    if (list != NULL && list->count > 0) {
        cur = list->first;
        while (cur != NULL) {
            next = cur->next;
            FileListItem_destroy(cur);
            cur = next;
        }
        list->count = 0;
    }
    free(list);
}

FileList *FileList_from_array(File **files, int count) {
    int i;
    FileList *list;
    FileListItem *cur, *tmp;

    list = FileList_new();
    cur = NULL;

    for (i = 0; i < count; i++) {
        tmp = FileListItem_new();
        tmp->file = File_clone(files[i]);

        if (cur == NULL) {
            list->first = tmp;
            cur = tmp;
        }
        else {
            cur->next = tmp;
            cur = cur->next;
        }
    }
    list->count = count;

    return list;
}

void FileList_add(FileList *list, File *file) {
    FileListItem *cur, *new;

    new = FileListItem_new();
    new->file = file;

    cur = list->first;
    if (cur == NULL) {
        list->first = new;
        list->count = 1;
    }
    else {
        while (cur != NULL) {
            if (cur->next == NULL) {
                cur->next = new;
                cur = cur->next;
                list->count++;
            }
            cur = cur->next;
        }
    }
}

File **FileList_to_array(FileList *list) {
    File **arr;
    FileListItem *cur;
    int i;

    arr = NULL;
    if (list->count > 0) {
        arr = malloc(list->count * sizeof(File *));
        if (arr == NULL) {
            handle_fatal_error(E_ALLOC);
        }

        i = 0;
        cur = list->first;
        while (cur != NULL) {
            arr[i] = File_clone(cur->file);
            i++;
            cur = cur->next;
        }
    }

    return arr;
}
