#include <stddef.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include "windows.h"
#include "sorting.h"
#include "utils.h"
#include "fileMapping.h"

#define FILE_START_SIZE 100000
#define FILE_GENERATE_STEP 100000
#define FILES_COUNT 10
#define MIN_KEY 0
#define MAX_KEY 100000
#define MIN_VAL_LEN 10
#define MAX_VAL_LEN 20

using namespace std;
FILE* out;


int compareRecords(Record first, Record second) {
    return first.key - second.key;
}

int compareSimpleRecords(SimpleRecord first, SimpleRecord second) {
    return first.key - second.key;
}

void writeSorted(char *path, SimpleRecord* arr, long size) {
    FILE* f = fopen(path, "w+");
    fprintf(f, "%ld\n", size);
    for (long i =0; i < size; i++) {
        fprintf(f, "%d %s\n", arr[i].key, arr[i].value);
    }
    fclose(f);
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

void testHeap() {
    printf("Test sorting with heap\n");
    out = fopen("heap_report.csv", "w");
    char fileName[100];
    fprintf(out, "size;heap time;\n");
    for (int i = 0; i < FILES_COUNT; i++) {
        sprintf(fileName, "unsorted/test%d.txt", i);
        clock_t heap_start = clock();
        long size;
        SimpleRecord *recs = readFile(fileName, &size);
        heapSort(recs, size, &compareSimpleRecords);
        clock_t heap_end = clock();
        double diff = (double)(heap_end - heap_start) / CLOCKS_PER_SEC;
        fprintf(out, "%ld;%f;\n", size, diff);
        printf("File %s read and sorted on %f s\nPress enter ", fileName, diff);
        sprintf(fileName, "byHeap/sorted%d.txt", i);
        writeSorted(fileName, recs, size);
        getchar();
        removeRecords(recs);
        printf("Memory free. Press enter ");
        getchar();
        printf("\r\n");
    }
    fclose(out);
    printf("\n\n\n");
}

void testMapping() {
    printf("Test sorting with mapping files\n");
    out = fopen("map_report.csv", "w");
    char fileName[100];
    char anotherName[100];
    fprintf(out, "size;mapping time;\n");
    for (int i = 0; i < FILES_COUNT; i++) {
        sprintf(fileName, "unsorted/test%d.txt", i);
        clock_t heap_start = clock();
        FileMapping inputMapping = createFileMapping(fileName, OPEN_EXISTING);
        initBASE((char *)inputMapping.pObjFile);
        createIndexFile(fileName, (char *)inputMapping.pObjFile, anotherName);
        FileMapping indexMap = createFileMapping(anotherName, OPEN_EXISTING);
        long fileSize = GetFileSize(indexMap.hFile, NULL);
        fileSize /= sizeof(Record);
        Record *recs = (Record *)indexMap.pObjFile;
        heapSort<Record>(recs, fileSize, compareRecords);
        double diff = (double)(clock() - heap_start) / CLOCKS_PER_SEC;
        fprintf(out, "%ld;%f;\n", fileSize, diff);
        printf("File %s read and sorted on %f s\n", fileName, diff);
        sprintf(fileName, "byMapping/sorted%d.txt", i);
        writeSorted(fileName, recs, fileSize);
        initBASE(0);
        removeFileMapping(inputMapping);
        removeFileMapping(indexMap);
        printf("Press enter for free memory ");
        getchar();
        printf("\n");
        printf("Memory free. Press enter ");
        getchar();
        printf("\r\n");
    }
    fclose(out);
    printf("\n\n\n");
}

void generateFiles() {
    long size = FILE_START_SIZE;
    char *fileName = (char *) malloc(100);
    printf("Generate files...\n");
    for (int i = 0; i < FILES_COUNT; i++, size += FILE_GENERATE_STEP) {
        sprintf(fileName, "unsorted/test%d.txt", i);
        printf("%s\t%ld\n", fileName, size);
        generateFile(fileName, size, MIN_KEY, MAX_KEY, MIN_VAL_LEN, MAX_VAL_LEN);
    }
    free(fileName);
}

int main() {
//    generateFiles();
    testMapping();
    testHeap();
    return 0;
}