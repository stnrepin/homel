#ifndef FILE_LIST_H_
#define FILE_LIST_H_

#include <stddef.h>
#include "file.h"

/**
 * Элемент односвязного списка.
 */
typedef struct _FileListItem {
    File *file;
    _FileListItem *next;
} FileListItem;

/**
 * Односвязный список.
 */
typedef struct {
    size_t count;
    FileListItem *first;
} FileList;

/**
 * Создает новый элемент односвязного списка.
 * 
 * @return FileListItem* Новый объект.
 */
FileListItem *FileListItem_new();

/**
 * Уничтожает элемент односвязного списка.
 * 
 * @param fitem Элемент.
 */
void FileListItem_destroy(FileListItem *fitem);

/**
 * Создает новый односвязный список.
 * 
 * @return FileList* Список.
 */
FileList *FileList_new();

/**
 * Уничтожает список.
 * 
 * @param list 
 */
void FileList_destroy(FileList *list);

#endif /* !FILE_LIST_H_ */
