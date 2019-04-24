#ifndef FILE_H_
#define FILE_H_

/**
 * Объект, хранящий информацию о файле в библиотеке.
 */
typedef struct {
    char *name;
    char **hgroups;
    char *rel_path;
} File;

/**
 * Создает новый объект File.
 * 
 * @return File* Новый объект.
 */
File *File_new();

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

/**
 * Выводит на экран информацию о файле.
 * 
 * @param file Файл.
 */
void File_print_info(File *file);

#endif /* !FILE_H_ */
