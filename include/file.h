#ifndef FILE_H_
#define FILE_H_

#include <stddef.h>

/**
 * Объект, представляющий TagPath.
 */
typedef struct {
    int count;
    char **tags;
} TagPath;

/**
 * Объект, хранящий информацию о файле в библиотеке.
 */
typedef struct {
    size_t id;
    TagPath **tpathes;
    int tps_count;
    char *rel_path;
} File;

/**
 * Создает новый пустой объект TagPath.
 *
 * @return TagPath Новый объект.
 */
TagPath *TagPath_new();

/**
 * Создает новый объект TagPath, с определенными значениями полей.
 *
 * @param tp_arr Массив строк тегов (порядок важен).
 * @param count Число строк в массиве.
 * @return TagPath Новый объект.
 */
TagPath *TagPath_build(char **tp_arr, int count);

/**
 * Уничтожает объект.
 *
 * @param tp TagPath.
 */
void TagPath_destroy(TagPath *tp);

/**
 * Создает точную копию данного объекта.
 *
 * @param tp Исходный объект.
 * @return TagPath Копия.
 */
TagPath *TagPath_clone(TagPath *tp);

/**
 * Создает новый пустой объект File.
 *
 * @return File Новый объект.
 */
File *File_new();

/**
 * Создает новый объект File, с определенными значениями полей.
 *
 * @param id ID файла.
 * @param tps Массив TagPath.
 * @param tps_count Количество элементов в tgs.
 * @param path Путь (относительно корня) до файла.
 * @return File Новый объект.
 */
File *File_build(int id, TagPath **tps, int tps_count, char *path);

/**
 * Уничтожает объект.
 *
 * @param file Файл.
 */
void File_destroy(File *file);

/**
 * Сравнивает два файла по значению.
 *
 * @param f1 Первый файл.
 * @param f2 Второй файл.
 * @return int Положительное число, если файлы равны. Иначе - 0.
 */
int File_equals(File *f1, File *f2);

#endif /* !FILE_H_ */

