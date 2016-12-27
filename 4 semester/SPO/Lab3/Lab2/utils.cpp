#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "utils.h"

//
// Реализация методов из заголовочного файла utils.h
//
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

char *selectName(const char *path) {
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
    char *buf = (char *) malloc(length * sizeof(char) + 1);
    memcpy(buf, nameStart, length);
    buf[length] = '\0';
    return buf;
}

char *selectDir(const char *path) {
    int i;
    char *dirEnd = (char *) path;
    for (i = 0; path[i] != '\0'; i++) {
        char sign = path[i];
        if (sign == '/' || sign == '\\') dirEnd = (char *) (path + i + 1);
    }
    char *buf = (char *) malloc((dirEnd - path) * sizeof(char) + 1);
    memcpy(buf, path, dirEnd - path);
    buf[dirEnd - path] = '\0';
    return buf;
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

int compareRecords(Record first, Record second) {
    return first.key - second.key;
}

void writeSorted(char *path, Record *arr, long size) {
    FILE* f = fopen(path, "w+");
    fprintf(f, "%ld\n", size);
    for (long i =0; i < size; i++) {
        char *buf = arr[i].value.getCStr();
        fprintf(f, "%d %s\n", arr[i].key, buf);
        free(buf);
    }
    fclose(f);
}
