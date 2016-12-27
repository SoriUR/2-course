//
// Created by User on 12.04.2016.
//
#include "stdio.h"
#include "fileMapping.h"
#include "sorting.h"
#include "utils.h"

void writeSorted(const char *path, Record *arr, long size) {
    FILE* f = fopen(path, "w+");
    fprintf(f, "%ld\n", size);
    for (long i =0; i < size; i++) {
        char buf[100];
        arr[i].value.getCStr(buf);
        fprintf(f, "%d %s\n", arr[i].key, buf);
    }
    fclose(f);
}

int compareRecords(Record first, Record second) {
    return first.key - second.key;
}

int main(int argc, const char* argv[]) {
    FileMapping inputMapping = createFileMapping(argv[1], OPEN_EXISTING);
    initBASE((char *)inputMapping.pObjFile);
    char indxFileName[100];
    createIndexFile(argv[1], (char *)inputMapping.pObjFile, indxFileName);
    FileMapping indexMap = createFileMapping(indxFileName, OPEN_EXISTING);
    long fileSize = GetFileSize(indexMap.hFile, NULL);
    fileSize /= sizeof(Record);
    Record *recs = (Record *)indexMap.pObjFile;
    heapSort<Record>(recs, fileSize, compareRecords);
    char sorted[100];
    sprintf(sorted, "sorted_%s", argv[1]);
    writeSorted(sorted, recs, fileSize);
    printf("Search key %s in %s\n", argv[2], argv[1]);
    int key;
    sscanf(argv[2], "%d", &key);
    int res = binarySearch(recs, fileSize, key);
    if (res < 0) {
        printf("Key %d not found in file %s\n", key, argv[1]);
    }
    else {
        while (recs[res].key == key) {
            char value[100];
            recs[res].value.getCStr(value);
            printf("Key %d with value %s on position %d in sorted file %s\n", key, value, res, argv[1]);
            res++;
        }
    }
    initBASE(0);
    removeFileMapping(inputMapping);
    removeFileMapping(indexMap);

}