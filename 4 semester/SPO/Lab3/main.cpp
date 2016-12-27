#include "Lab1\Lab1.h"
#include "Lab2\Lab2.h"
#include "windows.h"
#include "stdio.h"
int lab1() {
	const int init = 1024 * 512;
	const int step = 1024 * 512;
	const int count = 10;
    generate_files(count, init, step);
    printf("|%10s|%10s|%10s|%10s|\n", "Size", "C lib", "Windows", "CopyFile");
    for (int i = 0; i < count; i++) {
        char in[20];
        generate_name(i, in);
        char c_out[20];
        generate_name(i + 10, c_out);
        char win_out[20];
        generate_name(i + 20, win_out);
        char cp_out[20];
        generate_name(i + 30, cp_out);
        printf("|%10d|%10lld|%10lld|%10lld|\n", init + i * step, copy_c(in, c_out) / 10,
               copy_windows(in, win_out) /10,
               windows_copyfile(in, cp_out) / 10);
    }
    return 0;
}

int main() {
	printf("Using of assembler dll\n");
	HINSTANCE hDll = LoadLibrary("atanh_dll");
    if (hDll == NULL) {
        printf("NULL\n");
    }
    else {
        void _stdcall (*f) (double*, double*);
        f = (void _stdcall (*)(double *, double *))GetProcAddress(hDll, "ATANH");
        double res;
        if (f) {
            double arg = 2.0;
            f(&arg, &res);
            printf("atanh(%f) = %f\n", arg, res);
			arg = 4.0;
			f(&arg, &res);
            printf("atanh(%f) = %f\n", arg, res);
			arg = 5.0;
			f(&arg, &res);
            printf("atanh(%f) = %f\n", arg, res);
        }

        FreeLibrary(hDll);
    }
	printf("Using of Lab1 functions\n");
	lab1();
	generateFile("unsorted.txt", 1024 * 50, 0, 100000, 5, 20);
	char buf[100];
	FileMapping inputMapping = createFileMapping("unsorted.txt", OPEN_EXISTING);
        initBASE((char *)inputMapping.pObjFile);
        createIndexFile("unsorted.txt", (char *)inputMapping.pObjFile, buf);
        FileMapping indexMap = createFileMapping(buf, OPEN_EXISTING);
        long fileSize = GetFileSize(indexMap.hFile, NULL);
        fileSize /= sizeof(Record);
        Record *recs = (Record *)indexMap.pObjFile;
        heapSort<Record>(recs, fileSize, compareRecords);
        writeSorted("sorted.txt", recs, fileSize);
        initBASE(0);
        removeFileMapping(inputMapping);
        removeFileMapping(indexMap);
	return 0;
}