#include <stdio.h>
#include "windows.h"
#include "fileMapping.h"
#include "utils.h"

//
// Реализация функций из заголовочного файла fileMapping.h
//
char *_BASE_STR = nullptr;

char *BasedStr::getValue() {
    return _BASE_STR + offset;
}

void BasedStr::getCStr(char *buf) {
    for (int i = 0; i < length; i++) {
        buf[i] = _BASE_STR[offset + i];
    }
    buf[length] = '\0';
}

void initBASE(char *val) {
    _BASE_STR = val;
}

FileMapping createFileMapping(const char *path, DWORD dwCreationDisposition) {
    FileMapping res;
    res.hFile = CreateFile(path, GENERIC_READ | GENERIC_WRITE, 0, NULL, dwCreationDisposition, 0, NULL);
    DWORD fsLow = GetFileSize(res.hFile, NULL);
    res.hMapFile = CreateFileMapping(res.hFile, NULL, PAGE_READWRITE, 0, fsLow, NULL);
    res.pObjFile = MapViewOfFile(res.hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
    return res;
}

FileMapping createSizedFileMapping(const char *path, DWORD dwCreationDisposition, DWORD size) {
    FileMapping res;
    res.hFile = CreateFile(path, GENERIC_READ | GENERIC_WRITE, 0, NULL, dwCreationDisposition, 0, NULL);
    res.hMapFile = CreateFileMapping(res.hFile, NULL, PAGE_READWRITE, 0, size, NULL);
    res.pObjFile = MapViewOfFile(res.hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
    return res;
}

void removeFileMapping(FileMapping mapping) {
    UnmapViewOfFile(mapping.pObjFile);
    CloseHandle(mapping.hMapFile);
    CloseHandle(mapping.hFile);
}

//Не пытайтесь осознать костыли. Они есть.
char *skipUntilNewLine(char *in, int *skipped);

int readInt(char **in);

void createIndexFile(const char *path, char *inputMapping, char *indxName) {
    char *inputFileMapping = inputMapping;
    char name[50];
    selectName(path, name);
    char dir[50];
    selectDir(path, dir);
//    int len = strlen(name);
    sprintf(indxName, "%s.%s.indx", dir, name);
    int size = readInt(&inputFileMapping);
    DWORD fsLow = size * sizeof(Record);
    FileMapping map = createSizedFileMapping(indxName, CREATE_ALWAYS, fsLow);
    Record *records = (Record *) map.pObjFile;
    int skipped;
    inputFileMapping = skipUntilNewLine(inputFileMapping, &skipped);
    for (int i = 0; i < size; i++) {
        int key = readInt(&inputFileMapping);
        inputFileMapping++;
        size_t offset = inputFileMapping - _BASE_STR;
        inputFileMapping = skipUntilNewLine(inputFileMapping, &skipped);
        BasedStr based = {offset, skipped - 2};
        Record rec = {key, based};
        records[i] = rec;
    }
    removeFileMapping(map);
}

char *skipUntilNewLine(char *in, int *skipped) {
    *skipped = 0;
    while (*in != EOF && *in != '\0' && *in != '\r' && *(in + 1) != '\n') {
        in++;
        (*skipped)++;
    }
    *skipped += 2;
    return in + 2;
}

int readInt(char **in) {
    int buf = 0;
    char sign = **in;
    while ('0' <= sign && sign <= '9') {
        buf *= 10;
        buf += sign - '0';
        (*in)++;
        sign = **in;
    }
    return buf;
}
