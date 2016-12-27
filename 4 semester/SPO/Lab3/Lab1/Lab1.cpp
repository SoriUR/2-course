#include "windows.h"
#include "stdio.h"
#include "Lab1.h"
#define BUF_SIZE 256

void generate_name(int i, char *buf) {
    sprintf(buf, "./test%d.txt", i);
}

void generate_files(int count, int init_size, int step) {
    srand(1000);
    char buffer[BUF_SIZE];
    FILE* file;
    for (int i = 0; i < count; i++) {
		char buf[20];
        generate_name(i, buf);
        file = fopen(buf, "w");
        int count = init_size + step * i;
        int k = 0;
        for (int j = 0; j < count; j++) {
            buffer[k] = (char) (rand() % ('z' - '0') + '0');
            k++;
            if (k == BUF_SIZE) {
                fwrite(buffer, sizeof(char), BUF_SIZE, file);
                k = 0;
            }
        }
        fclose(file);
    }
    return;
}

long long get_diff(SYSTEMTIME begin, SYSTEMTIME end) {
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

long long copy_c(char *in_path, char *out_path) {
    char buffer[BUF_SIZE];
    SYSTEMTIME begin;
    GetSystemTime(&begin);
    FILE *input = fopen(in_path, "r");
    FILE *output = fopen(out_path, "w");
    unsigned int c;
    while ((c = fread(buffer, sizeof(char), BUF_SIZE, input)) > 0) {
        fwrite(buffer, sizeof(char), c, output);
    }
    fclose(input);
    fclose(output);
    SYSTEMTIME end;
    GetSystemTime(&end);
    return get_diff(begin, end);
}

long long copy_windows(char *in_path, char *out_path) {
    SYSTEMTIME begin;
    GetSystemTime(&begin);
    HANDLE hIn = CreateFile(in_path, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0 , NULL);
    HANDLE hOut = CreateFile(out_path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    char buffer[BUF_SIZE];
    DWORD read_sym;
    DWORD write_sym;
    do {
        ReadFile(hIn, buffer, BUF_SIZE, &read_sym, NULL);
        WriteFile(hOut, buffer, read_sym, &write_sym, NULL);
    } while (read_sym > 0);
    CloseHandle(hIn);
    CloseHandle(hOut);
    SYSTEMTIME end;
    GetSystemTime(&end);
    return get_diff(begin, end);
}
long long int windows_copyfile(char *in_path, char *out_path) {
    SYSTEMTIME begin;
    GetSystemTime(&begin);
    CopyFile(in_path, out_path, false);
    SYSTEMTIME end;
    GetSystemTime(&end);
    return get_diff(begin, end);
}