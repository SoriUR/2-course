//
// Функции без рода и племени
//
#include "windows.h"
#include "fileMapping.h"
#ifndef LAB2_UTILS_H
#define LAB2_UTILS_H
struct SimpleRecord {
    int key;
    char *value;
};

void selectName(const char *path, char *res);
void selectDir(const char *path, char *res);

bool checkSorted(int *arr, long left, long right);
void generateFile(char *path, long size, int minKeyValue, int maxKeyValue, int minValLen, int maxValLen);
void writeIntArrToFile(int *arr, long arrSize, char *path);
int randInt(int min, int max);
char *randStr(int size);
SimpleRecord *readFile(char *path, long *size);
void removeRecords(SimpleRecord *records);
long long getTimeSpan(SYSTEMTIME begin, SYSTEMTIME end);
long long int windows_copyfile(char *in_path, char *out_path);
int binarySearch(Record *arr, int size, int key);
#endif //LAB2_UTILS_H
