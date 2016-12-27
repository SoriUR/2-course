//
// Объявление функций для работы с представлениями файлов
//
#include "windows.h"
#ifndef LAB2_FILEMAPPING_H
#define LAB2_FILEMAPPING_H

/* Базовый указатель для стуктур BasedStr
 * Они хранят смещение относительно начала _BASE_STR
 * Чтобы получать корректные значения методами getValue и getCStr, необходимо проинициализировать эту переменную
*/
extern char *_BASE_STR;

struct FileMapping {
    HANDLE hFile;
    HANDLE hMapFile;
    LPVOID pObjFile;
};

struct BasedStr {
    size_t offset;
    int length;
public:
    char *getValue();
    void getCStr(char *buf);
};

struct Record {
    int key;
    BasedStr value;
};

FileMapping createFileMapping(const char *path, DWORD dwCreationDisposition);
FileMapping createSizedFileMapping(const char *path, DWORD dwCreationDisposition, DWORD size);

void initBASE(char *val);

void removeFileMapping(FileMapping mapping);
/*
 * Принимает на вход путь к файлу path, содержащего в первой строке количество записей n,
 * в последующих n строках содержатся пары ключ-значение, разделенные одим символом (любым, кроме перевода строки),
 * и массив char (представление индексируемого файла в памяти)
 * Создает файл индексный файл папка/.имя_файла.indx
 */
void createIndexFile(const char *path, char *inputFileMapping, char *indxName);

#endif //LAB2_FILEMAPPING_H
