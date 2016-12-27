//
// Объявление функций для работы с представлениями файлов
//

#ifndef LAB2_FILEMAPPING_H
#define LAB2_FILEMAPPING_H
#include "windows.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef LAB2_DLL
#define LAB2_DLL_API __declspec(dllexport)
#else
#define LAB2_DLL_API __declspec(dllimport)
#endif

/* Базовый указатель для стуктур BasedStr
 * Они хранят смещение относительно начала _BASE_STR
 * Чтобы получать корректные значения методами getValue и getCStr, необходимо проинициализировать эту переменную
*/
extern char *_BASE_STR;

struct LAB2_DLL_API FileMapping {
    HANDLE hFile;
    HANDLE hMapFile;
    LPVOID pObjFile;
};

struct LAB2_DLL_API BasedStr {
    size_t offset;
    int length;
public:
    char *getValue();
    char *getCStr();
};

struct LAB2_DLL_API Record {
    int key;
    BasedStr value;
};

FileMapping LAB2_DLL_API createFileMapping(const char *path, DWORD dwCreationDisposition);
FileMapping LAB2_DLL_API createSizedFileMapping(const char *path, DWORD dwCreationDisposition, DWORD size);

void LAB2_DLL_API initBASE(char *val);

void LAB2_DLL_API removeFileMapping(FileMapping mapping);
/*
 * Принимает на вход путь к файлу path, содержащего в первой строке количество записей n,
 * в последующих n строках содержатся пары ключ-значение, разделенные одим символом (любым, кроме перевода строки),
 * и массив char (представление индексируемого файла в памяти)
 * Создает файл индексный файл папка/.имя_файла.indx
 */
void LAB2_DLL_API createIndexFile(const char *path, char *inputFileMapping, char *indxName);

#ifdef __cplusplus
}
#endif

#endif //LAB2_FILEMAPPING_H
