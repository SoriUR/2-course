//
// Created by User on 12.04.2016.
//
#include "stdio.h"
#include "fileMapping.h"
#include "sorting.h"
#include "utils.h"

#define THREADS_COUNT 3

int compareRecords(Record first, Record second) {
    return first.key - second.key;
}

void doSort(FileMapping *input, FileMapping *index, const char *fileName, unsigned int *size) {
    *input = createFileMapping(fileName, OPEN_EXISTING);
    initBASE((char *) (*input).pObjFile);
    char indxFileName[100];
    createIndexFile(fileName, (char *) (*input).pObjFile, indxFileName);
    *index = createFileMapping(indxFileName, OPEN_EXISTING);
    unsigned int fileSize = GetFileSize((*index).hFile, NULL);
    fileSize /= sizeof(Record);
    *size = fileSize;
    Record *recs = (Record *) (*index).pObjFile;
    heapSort<Record>(recs, fileSize, compareRecords);
}

struct ThreadParams {
    Record *array;
    unsigned int size;
    int key;
    int threadNumber;
};

CRITICAL_SECTION csLock;

DWORD WINAPI criticalSections(LPVOID arg) {
    ThreadParams *params = (ThreadParams *) arg;
    EnterCriticalSection(&csLock);
    printf("Start thread number %d\n", params->threadNumber);
    int res = binarySearch(params->array, params->size, params->key);
    LeaveCriticalSection(&csLock);
    if (res < 0) {
        EnterCriticalSection(&csLock);
        printf("th%d:Key %d not found\n", params->threadNumber, params->key);
        LeaveCriticalSection(&csLock);
    }
    else {
        int count = res;
        while (params->array[count].key == params->key) {
            count++;
        }
        EnterCriticalSection(&csLock);
        printf("%d values with key %d were found in sorted array, starts with %d index\n", count - res, params->key,
               res);
        LeaveCriticalSection(&csLock);
    }
    EnterCriticalSection(&csLock);
    printf("End thread %d\n", params->threadNumber);
    LeaveCriticalSection(&csLock);
    return 0;
}

HANDLE MUTEX;

DWORD  WINAPI mutexes(LPVOID arg) {
    ThreadParams *params = (ThreadParams *) arg;
    WaitForSingleObject(MUTEX, INFINITE);
    printf("Start thread number %d\n", params->threadNumber);
    int res = binarySearch(params->array, params->size, params->key);
    ReleaseMutex(MUTEX);
    if (res < 0) {
        WaitForSingleObject(MUTEX, INFINITE);
        printf("th%d:Key %d not found\n", params->threadNumber, params->key);
        ReleaseMutex(MUTEX);
    }
    else {
        int count = res;
        while (params->array[count].key == params->key) {
            count++;
        }
        WaitForSingleObject(MUTEX, INFINITE);
        printf("%d values with key %d were found in sorted array, starts with %d index\n", count - res, params->key,
               res);
        ReleaseMutex(MUTEX);
    }
    WaitForSingleObject(MUTEX, INFINITE);
    printf("End thread %d\n", params->threadNumber);
    ReleaseMutex(MUTEX);
    return 0;
}
HANDLE EVENT;

DWORD  WINAPI eventBased(LPVOID arg) {
    ThreadParams *params = (ThreadParams *) arg;
    WaitForSingleObject(EVENT, INFINITE);
    printf("Start thread number %d\n", params->threadNumber);
    int res = binarySearch(params->array, params->size, params->key);
    SetEvent(EVENT);
    if (res < 0) {
        WaitForSingleObject(EVENT, INFINITE);
        printf("th%d:Key %d not found\n", params->threadNumber, params->key);
        SetEvent(EVENT);
    }
    else {
        int count = res;
        while (params->array[count].key == params->key) {
            count++;
        }
        WaitForSingleObject(EVENT, INFINITE);
        printf("%d values with key %d were found in sorted array, starts with %d index\n", count - res, params->key,
               res);
        SetEvent(EVENT);
    }
    WaitForSingleObject(EVENT, INFINITE);
    printf("End thread %d\n", params->threadNumber);
    SetEvent(EVENT);
    return 0;
}
HANDLE SEMAPHORE;

DWORD  WINAPI semaphoreBased(LPVOID arg) {
    ThreadParams *params = (ThreadParams *) arg;
    WaitForSingleObject(SEMAPHORE, INFINITE);
    printf("Start thread number %d\n", params->threadNumber);
    int res = binarySearch(params->array, params->size, params->key);
    ReleaseSemaphore(SEMAPHORE, 1, NULL);
    if (res < 0) {
        WaitForSingleObject(SEMAPHORE, INFINITE);
        printf("th%d:Key %d not found\n", params->threadNumber, params->key);
        ReleaseSemaphore(SEMAPHORE, 1, NULL);
    }
    else {
        int count = res;
        while (params->array[count].key == params->key) {
            count++;
        }
        WaitForSingleObject(SEMAPHORE, INFINITE);
        printf("%d values with key %d were found in sorted array, starts with %d index\n", count - res, params->key,
               res);
        ReleaseSemaphore(SEMAPHORE, 1, NULL);
    }
    WaitForSingleObject(SEMAPHORE, INFINITE);
    printf("End thread %d\n", params->threadNumber);
    ReleaseSemaphore(SEMAPHORE, 1, NULL);
    return 0;
}

void processThreads(LPTHREAD_START_ROUTINE function, ThreadParams *params, unsigned long *ids, HANDLE *handles) {
    for (int i = 0; i < THREADS_COUNT; i++) {
        handles[i] = CreateThread(NULL, 0, function, &params[i], 0, &ids[i]);
    }
    WaitForMultipleObjects(THREADS_COUNT, handles, TRUE, INFINITE);
    for (int i = 0; i < THREADS_COUNT; i++) {
        FILETIME creation, exit, kernel, user;
        SYSTEMTIME creationSys, exitSys;
        ULARGE_INTEGER kernelUINT, userUINT;
        GetThreadTimes(handles[i], &creation, &exit, &kernel, &user);
        FileTimeToSystemTime(&creation, &creationSys);
        FileTimeToSystemTime(&exit, &exitSys);
        kernelUINT.LowPart = kernel.dwLowDateTime;
        kernelUINT.HighPart = kernel.dwHighDateTime;
        userUINT.LowPart = user.dwLowDateTime;
        userUINT.HighPart = user.dwHighDateTime;
        printf("\n\nThread %d info\n", params[i].threadNumber);
        printf("ID:%ld\n", ids[i]);
        printf("Start time: %d:%d:%d\n", creationSys.wHour, creationSys.wMinute, creationSys.wMilliseconds);
        printf("End time: %d:%d:%d\n", exitSys.wHour, exitSys.wMinute, exitSys.wMilliseconds);
        printf("Kernel time: %llu\n", kernelUINT.QuadPart);
        printf("User time: %llu\n\n\n", userUINT.QuadPart);
    }
    for (int i = 0; i < THREADS_COUNT; i++) {
        CloseHandle(handles[i]);
    }
}

int main(int argc, const char *argv[]) {
    FileMapping inputMapping;
    FileMapping indexMap;
    unsigned int fileSize;
    InitializeCriticalSection(&csLock);
    doSort(&inputMapping, &indexMap, "1.txt", &fileSize);

    Record *recs = (Record *) indexMap.pObjFile;
    ThreadParams params[THREADS_COUNT];
    for (int i = 0; i < THREADS_COUNT; i++) {
        params[i] = {recs, fileSize, i + 1, i + 1};
    }
    unsigned long threadIds[THREADS_COUNT];
    HANDLE handles[THREADS_COUNT];

    printf("\n\n\n==========\nCRITICAL SECTIONS\n==========\n\n");
    processThreads(&criticalSections, params, threadIds, handles);

    MUTEX = CreateMutex(NULL, FALSE, NULL);
    printf("\n\n\n==========\nMUTEXES\n==========\n\n");
    processThreads(&mutexes, params, threadIds, handles);
    CloseHandle(MUTEX);

    printf("\n\n\n==========\nSEMAPHORES\n==========\n\n");
    SEMAPHORE = CreateSemaphore(NULL, 1, 1, NULL);
    processThreads(&semaphoreBased, params, threadIds, handles);

    printf("\n\n\n==========\nEVENTS\n==========\n\n");
    EVENT = CreateEvent(NULL, FALSE, TRUE, NULL);
    processThreads(&eventBased, params, threadIds, handles);
    CloseHandle(EVENT);

    initBASE(0);
    removeFileMapping(inputMapping);
    removeFileMapping(indexMap);
    return 0;
}