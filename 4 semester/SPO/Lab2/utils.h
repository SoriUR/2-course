//
// Функции без рода и племени
//

#ifndef LAB2_UTILS_H
#define LAB2_UTILS_H
struct SimpleRecord {
    int key;
    char *value;
};

char *selectName(const char *path);
char *selectDir(const char *path);

bool checkSorted(int *arr, long left, long right);
void generateFile(char *path, long size, int minKeyValue, int maxKeyValue, int minValLen, int maxValLen);
void writeIntArrToFile(int *arr, long arrSize, char *path);
int randInt(int min, int max);
char *randStr(int size);
SimpleRecord *readFile(char *path, long *size);
void removeRecords(SimpleRecord *records);

#endif //LAB2_UTILS_H
