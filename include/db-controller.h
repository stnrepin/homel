#ifndef DB_CONTROLLER_H_
#define DB_CONTROLLER_H_

#include "file.h"
#include "file-list.h"

/**
 * Загружает список файлов.
 * 
 * @return FileList* Загруженный список.
 */
FileList *load_files();

/**
 * Сохраняет список в индекс.
 * 
 * @return FileList* Список файлов.
 */
FileList *save_files(FileList *list);

#endif /* !DB_CONTROLLER_H_ */
