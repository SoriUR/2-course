//
// Функции без рода и племени
//

#ifndef LAB2_UTILS_H
#define LAB2_UTILS_H
#include "fileMapping.h"
#include "windows.h"
#ifdef __cplusplus
extern "C" {
#endif

#ifdef LAB2_DLL
#define LAB2_DLL_API __declspec(dllexport)
#else
#define LAB2_DLL_API __declspec(dllimport)
#endif

struct LAB2_DLL_API SimpleRecord {
    int key;
    char *value;
};

char LAB2_DLL_API *selectName(const char *path);
char LAB2_DLL_API *selectDir(const char *path);
int LAB2_DLL_API randInt(int min, int max);
char LAB2_DLL_API *randStr(int size);
int LAB2_DLL_API compareRecords(Record first, Record second);
void LAB2_DLL_API writeSorted(char *path, Record *arr, long size);
void LAB2_DLL_API generateFile(char *path, long size, int minKeyValue, int maxKeyValue, int minValLen, int maxValLen);

#ifdef __cplusplus
}
#endif

#endif //LAB2_UTILS_H
