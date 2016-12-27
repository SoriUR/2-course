#include "windows.h"
#include "stdio.h"
#include "utils.h"

#define FILE1_NAME "1.txt"
#define FILE2_NAME "2.txt"
#define FILE3_NAME "3.txt"
#define FILE_SIZE 128*1024
#define MIN_KEY 1
#define MAX_KEY 5*1024*1024
#define MIN_VALUE_LEN 5
#define MAX_VALUE_LEN 25

void printProcessInfo(int i, PROCESS_INFORMATION info) {
    FILETIME creationTime, exitTime, kernelTime, userTime;
    SYSTEMTIME sysCreationTime, sysExitTime, sysKernelTime, sysUserTime;
    GetProcessTimes(info.hProcess, &creationTime, &exitTime, &kernelTime, &userTime);
    FileTimeToSystemTime(&creationTime, &sysCreationTime);
    ULARGE_INTEGER bufLargeInteger;
    printf("\n\n\n============\nProcess %d info\n", i);
    printf("Process ID: %ld\n", info.dwProcessId);
    long handleCount;
    printf("Creation date: %d/%d/%d %d:%d:%d\n", sysCreationTime.wDay, sysCreationTime.wMonth,
           sysCreationTime.wYear, sysCreationTime.wHour, sysCreationTime.wMinute, sysCreationTime.wMilliseconds);
    bufLargeInteger.LowPart = creationTime.dwLowDateTime;
    bufLargeInteger.HighPart = creationTime.dwHighDateTime;
    printf("\t%lld mks\n", bufLargeInteger.QuadPart / 10);
    FileTimeToSystemTime(&exitTime, &sysExitTime);
    printf("Exit date: %d/%d/%d %d:%d:%d\n", sysExitTime.wDay, sysExitTime.wMonth,
           sysExitTime.wYear, sysExitTime.wHour, sysExitTime.wMinute, sysExitTime.wMilliseconds);
    bufLargeInteger.LowPart = exitTime.dwLowDateTime;
    bufLargeInteger.HighPart = exitTime.dwHighDateTime;
    printf("\t%lld mks\n", bufLargeInteger.QuadPart / 10);
    bufLargeInteger.LowPart = kernelTime.dwLowDateTime;
    bufLargeInteger.HighPart = kernelTime.dwHighDateTime;
    printf("Kernel time: %lld mks\n", bufLargeInteger.QuadPart / 10);
    bufLargeInteger.LowPart = userTime.dwLowDateTime;
    bufLargeInteger.HighPart = userTime.dwHighDateTime;
    printf("User time: %lld mks\n", bufLargeInteger.QuadPart / 10);
    printf("============\n");
}

int main(int argc, const char *argv[]) {


    generateFile(FILE1_NAME, FILE_SIZE, MIN_KEY, MAX_KEY, MIN_VALUE_LEN, MAX_VALUE_LEN);
    generateFile(FILE2_NAME, FILE_SIZE, MIN_KEY, MAX_KEY, MIN_VALUE_LEN, MAX_VALUE_LEN);
    generateFile(FILE3_NAME, FILE_SIZE, MIN_KEY, MAX_KEY, MIN_VALUE_LEN, MAX_VALUE_LEN);
    int key;
    sscanf(argv[1], "%d", &key);
    char cmd[1024];
    sprintf(cmd, "sort_find %s %d", FILE1_NAME, key);
    STARTUPINFO stup;
    GetStartupInfo(&stup);
    PROCESS_INFORMATION firstProcessInformation, secondProcessInformation, thirdProcessInformation;
    printf("==============\nPROCESS 1\n==============\n");
    CreateProcess(NULL, cmd, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &stup, &firstProcessInformation);
    WaitForSingleObject(firstProcessInformation.hProcess, INFINITE);
    sprintf(cmd, "sort_find %s %d", FILE2_NAME, key);
    printf("\n==============\nPROCESS 2\n==============\n");
    CreateProcess(NULL, cmd, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &stup, &secondProcessInformation);
    WaitForSingleObject(secondProcessInformation.hProcess, INFINITE);
    sprintf(cmd, "sort_find %s %d", FILE3_NAME, key);
    printf("\n==============\nPROCESS 3\n==============\n");
    CreateProcess(NULL, cmd, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &stup, &thirdProcessInformation);
    WaitForSingleObject(thirdProcessInformation.hProcess, INFINITE);

    printProcessInfo(1, firstProcessInformation);
    printProcessInfo(2, secondProcessInformation);
    printProcessInfo(3, thirdProcessInformation);

    CloseHandle(firstProcessInformation.hThread);
    CloseHandle(firstProcessInformation.hProcess);
    CloseHandle(secondProcessInformation.hThread);
    CloseHandle(secondProcessInformation.hProcess);
    CloseHandle(thirdProcessInformation.hThread);
    CloseHandle(thirdProcessInformation.hProcess);
    return 0;
}