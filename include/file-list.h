#ifndef FILE_LIST_H_
#define FILE_LIST_H_

#include "file.h"

/**
 * Элемент односвязного списка.
 */
typedef struct _FileListItem {
    File *file;
    struct _FileListItem *next;
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

/**
 * Создает новый список из массива (элементы копируются).
 *
 * @param files Массив.
 * @param count Количество элементов в массиве.
 * @return Новый список.
 */
FileList *FileList_from_array(File **files, int count);

/**
 * Добавляет новый элемент в список.
 *
 * @param list Список.
 * @param file Новый элемент.
 */
void FileList_add(FileList *list, File *file);

/**
 * Преобразует список в массив.
 *
 * @param files Список
 * @return Массив.
 */
File **FileList_to_array(FileList *list);

#endif /* !FILE_LIST_H_ */

