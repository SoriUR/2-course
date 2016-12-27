#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "utils.h"
#include "windows.h"
#include "fileMapping.h"

//
// Реализация методов из заголовочного файла utils.h
//
char *all_values;
char *end;
size_t READ_SIZE;
void selectName(const char *path, char* res) {
    char *nameStart = (char *) path;
    char *iter = (char *) path;
    int length = 0;
    while (*iter != '\0') {
        char sign = *iter;
        if (sign == '/' || sign == '\\') {
            nameStart = iter + 1;
            length = 0;
        } else {
            length++;
        }
        iter++;
    }
    memcpy(res, nameStart, length);
}

long long getTimeSpan(SYSTEMTIME begin, SYSTEMTIME end) {
    FILETIME first;
    SystemTimeToFileTime(&begin, &first);
    FILETIME second;
    SystemTimeToFileTime(&end, &second);
    ULARGE_INTEGER f;
    f.HighPart = first.dwHighDateTime;
    f.LowPart = first.dwLowDateTime;
    ULARGE_INTEGER s;
    s.LowPart = second.dwLowDateTime;
    s.HighPart = second.dwHighDateTime;
    return s.QuadPart - f.QuadPart;
}

long long int windows_copyfile(char *in_path, char *out_path) {
    SYSTEMTIME begin;
    GetSystemTime(&begin);
    CopyFile(in_path, out_path, false);
    SYSTEMTIME end;
    GetSystemTime(&end);
    return getTimeSpan(begin, end);
}

void selectDir(const char *path, char *res) {
    int i;
    char *dirEnd = (char *) path;
    for (i = 0; path[i] != '\0'; i++) {
        char sign = path[i];
        if (sign == '/' || sign == '\\') dirEnd = (char *) (path + i + 1);
    }
    if (dirEnd - path > 0) {
        memcpy(res, path, dirEnd - path);
    }

}

bool checkSorted(int *arr, long left, long right) {
    long i;
    for (i = left; i < right; i++) {
        if (arr[i] > arr[i+1]) return false;
    }
    return true;
}

void generateFile(char *path, long size, int minKeyValue, int maxKeyValue, int minValLen, int maxValLen) {
    srand(time(NULL));
    FILE *file = fopen(path, "w");
    long i;
    int next;
    fprintf(file, "%ld\n", size);
    for (i = 0; i < size; i++) {
        next = randInt(minKeyValue, maxKeyValue);
        int len = randInt(minValLen, maxValLen);
        char *value = randStr(len);
        fprintf(file, "%d %s\n", next, value);
        free(value);
    }
    fclose(file);
}

void writeIntArrToFile(int *arr, long arrSize, char *path) {
    FILE *file = fopen(path, "w");
    if (file == NULL) return;
    fprintf(file, "%ld\n", arrSize);
    long i;
    for (i = 0; i < arrSize; i++) {
        fprintf(file, "%d\n", arr[i]);
    }
    fclose(file);
}

SimpleRecord *readFile(char *path, long *size) {
    READ_SIZE = 0;
    FILE *file = fopen(path, "r");
    if (file == NULL) return NULL;
    fscanf(file, "%ld", size);
    long i;
    long s = *size;
    char *buf = (char *) malloc(100);
    all_values = (char *)malloc(s * 20);
    end = all_values;
    SimpleRecord *res = (SimpleRecord *) malloc(s * sizeof(SimpleRecord));
    for (i = 0; i < s; i++) {
        int key;
        fscanf(file, "%d%*c%s", &key, buf);
        int len = strlen(buf);
        strcpy(end, buf);
        res[i] = {key, end};
        end += len + 1;
        READ_SIZE += len + 1;
    }
    realloc(all_values, READ_SIZE);
    free(buf);
    fclose(file);
    return res;
}

int randInt(int min, int max) {
    if (min == max) return min;
    int range = max - min + 1;
    return rand() % range + min;
}

char randChar(char low, char high) {
    if (low == high) return low;
    int range = high - low + 1;
    return rand() % range + low;
}

char *randStr(int size) {
    char *res = (char *) malloc(size);
    for (int i = 0; i < size; i++) {
        res[i] = randChar('0', 'z');
    }
    res[size - 1] = '\0';
    return res;
}

void removeRecords(SimpleRecord *records) {
    free(all_values);
    free(records);
}

int binarySearch(Record *arr, int size, int key) {
    int l = 0, r = size - 1, q = 0;
    Record qval;
    while (l < r) {
        q = l + (r - l) / 2;
        qval = arr[q];
        if (key <= qval.key) r = q;
        else l = q + 1;
    }
    if (arr[r].key == key) return r;
    return -1;
}
