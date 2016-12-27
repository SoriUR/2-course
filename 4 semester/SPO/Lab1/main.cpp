#include "windows.h"
#include "stdio.h"
#define BUF_SIZE 256
#define FILE_PART_SIZE 5 * 1024 * 1024
enum disciplines_kinds {
    exam, test
};
struct discipline {
    char *name;
    double points;
    disciplines_kinds kind;
    char get() {
        switch (kind) {
            case exam: {
                if (points < 60.0) return '-';
                if (points <= 67.0) return 'E';
                if (points <= 74.0) return 'D';
                if (points <= 83.0) return 'C';
                if (points <= 90.0) return 'B';
                return 'A';
            }
            case test: {
                if (points < 60.0) return 'f';
                return 'p';
            }
        }
    }
};
struct semester_results {
    int number;
    discipline disciplines[10];
};
void generate_name(int i, char *buf) {
    sprintf(buf, "./test%d.txt", i);
}
void generate_files() {
    srand(1000);
    char buffer[BUF_SIZE];
    FILE* file;
    printf("Generate files...\n");
    for (int i = 1; i <= 10; i++) {
        char buf[20];
        generate_name(i, buf);
        file = fopen(buf, "w");
        int count = FILE_PART_SIZE * i;
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
void init_first_semester(semester_results *first) {
    first->number = 1;
    first->disciplines[0].name = "Иностранный язык";
    first->disciplines[0].kind = disciplines_kinds::test;
    first->disciplines[0].points = 73;

    first->disciplines[1].name = "Информатика";
    first->disciplines[1].points = 92;
    first->disciplines[1].kind = disciplines_kinds::exam;

    first->disciplines[2].name = "Культурология";
    first->disciplines[2].kind = disciplines_kinds::test;
    first->disciplines[2].points = 91;

    first->disciplines[3].name = "Математика";
    first->disciplines[3].points = 91;
    first->disciplines[3].kind = disciplines_kinds::exam;

    first->disciplines[4].name = "Основы вычислительной техники";
    first->disciplines[4].kind = disciplines_kinds::test;
    first->disciplines[4].points = 79.57;

    first->disciplines[5].name = "Основы права";
    first->disciplines[5].kind = disciplines_kinds::test;
    first->disciplines[5].points = 91;

    first->disciplines[6].name = "Основы программирования";
    first->disciplines[6].kind = disciplines_kinds::exam;
    first->disciplines[6].points = 91.9;

    first->disciplines[7].name = "Риторика";
    first->disciplines[7].kind = disciplines_kinds::test;
    first->disciplines[7].points = 69.74;

    first->disciplines[8].name = "Физика";
    first->disciplines[8].kind = disciplines_kinds::exam;
    first->disciplines[8].points = 94.65;

    first->disciplines[9].name = "Физическая культура";
    first->disciplines[9].kind = disciplines_kinds::test;
    first->disciplines[9].points = 94;

}

void init_second_semester(semester_results *second) {
    second->number = 2;
    second->disciplines[0].name = "Иностранный язык";
    second->disciplines[0].kind = disciplines_kinds::test;
    second->disciplines[0].points = 71;

    second->disciplines[1].name = "Дискретная математика";
    second->disciplines[1].points = 94;
    second->disciplines[1].kind = disciplines_kinds::exam;

    second->disciplines[2].name = "История";
    second->disciplines[2].kind = disciplines_kinds::test;
    second->disciplines[2].points = 67.5;

    second->disciplines[3].name = "Математика";
    second->disciplines[3].points = 97.5;
    second->disciplines[3].kind = disciplines_kinds::exam;

    second->disciplines[4].name = "Комбинаторные алгоритмы";
    second->disciplines[4].kind = disciplines_kinds::test;
    second->disciplines[4].points = 80.51;

    second->disciplines[5].name = "Математическая логика";
    second->disciplines[5].kind = disciplines_kinds::test;
    second->disciplines[5].points = 90;

    second->disciplines[6].name = "Основы программирования";
    second->disciplines[6].kind = disciplines_kinds::exam;
    second->disciplines[6].points = 91.5;

    second->disciplines[7].name = "Основы вычислительной техники";
    second->disciplines[7].kind = disciplines_kinds::exam;
    second->disciplines[7].points = 92;

    second->disciplines[8].name = "Физика";
    second->disciplines[8].kind = disciplines_kinds::exam;
    second->disciplines[8].points = 91.9;

    second->disciplines[9].name = "Физическая культура";
    second->disciplines[9].kind = disciplines_kinds::test;
    second->disciplines[9].points = 93;

}

void init_third_semester(semester_results *third) {
    third->number = 3;
    third->disciplines[0].name = "Иностранный язык";
    third->disciplines[0].kind = disciplines_kinds::test;
    third->disciplines[0].points = 75;

    third->disciplines[1].name = "Вычислительная математика";
    third->disciplines[1].points = 100;
    third->disciplines[1].kind = disciplines_kinds::exam;

    third->disciplines[2].name = "Основы программной инженерии";
    third->disciplines[2].kind = disciplines_kinds::test;
    third->disciplines[2].points = 85;

    third->disciplines[3].name = "Математика";
    third->disciplines[3].points = 97;
    third->disciplines[3].kind = disciplines_kinds::exam;

    third->disciplines[4].name = "Программирование интернет-приложений";
    third->disciplines[4].kind = disciplines_kinds::test;
    third->disciplines[4].points = 92.65;

    third->disciplines[5].name = "Экономика";
    third->disciplines[5].kind = disciplines_kinds::test;
    third->disciplines[5].points = 67.57;

    third->disciplines[6].name = "Системное программное обеспечение";
    third->disciplines[6].kind = disciplines_kinds::exam;
    third->disciplines[6].points = 91;

    third->disciplines[7].name = "Языки системного программирования";
    third->disciplines[7].kind = disciplines_kinds::exam;
    third->disciplines[7].points = 91;

    third->disciplines[8].name = "Физика";
    third->disciplines[8].kind = disciplines_kinds::exam;
    third->disciplines[8].points = 90.08;

    third->disciplines[9].name = "Физическая культура";
    third->disciplines[9].kind = disciplines_kinds::test;
    third->disciplines[9].points = 83;

}
int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    char *buf = (char *)malloc((MAX_PATH + 2) * sizeof(char));
    GetCurrentDirectory(MAX_PATH + 2, buf);
    printf("Текущий каталог: %s\n", buf);
    free(buf);
    semester_results results[3];
    init_first_semester(&results[0]);
    init_second_semester(&results[1]);
    init_third_semester(&results[2]);
    FILE* output = fopen("./output.txt", "w");
    double all = 0;
    for (int i = 0; i < 3; i++) {
        double average = 0;
        printf("Семестр %d\n-------------------------------------------------------------------\n", results[i].number);
        fprintf(output, "Семестр %d\n-------------------------------------------------------------------\n", results[i].number);
        printf("|%-37s|Экзамен|Зачёт|Балл  |Оценка|\n", "Предмет");
        fprintf(output, "|%-37s|Экзамен|Зачёт|Балл  |Оценка|\n", "Предмет");
        for (int j = 0; j < 10; j++) {
            discipline curr = results[i].disciplines[j];
            average += curr.points;
            printf("|%-37s|", curr.name);
            fprintf(output, "|%-37s|", curr.name);
            if (curr.kind == disciplines_kinds::exam) {
                printf("   +   |     |");
                fprintf(output, "   +   |     |");
            }
            else {
                printf("       |  +  |");
                fprintf(output, "       |  +  |");
            }
            char point = curr.get();

            printf("%6.2f|", curr.points);
            fprintf(output, "%6.2f|", curr.points);
            if (point == 'p') {
                printf("зач   |\n");
                fprintf(output, "зач   |\n");
            } else if (point == 'f') {
                printf("незач |\n");
                fprintf(output, "незач |\n");
            } else {
                printf("%-6c|\n", point);
                fprintf(output, "%-6c|\n", point);
            }
        }
        printf("Средний балл: %f\n", average/10);
        fprintf(output, "Средний балл: %f\n", average/10);
        all += average;
        printf("-------------------------------------------------------------------\n\n");
        fprintf(output, "-------------------------------------------------------------------\n\n");
    }
    printf("Средний балл по результатам всех семестров: %f\n", all / 30);
    fprintf(output, "Средний балл по результатам всех семестров: %f\n", all / 30);
    printf("=====================\n\n\n");
//    generate_files();
    printf("|%10s|%10s|%10s|%10s|\n", "размер", "C lib", "Windows", "CopyFile");
    for (int i = 1; i <= 10; i++) {
        char in[20];
        generate_name(i, in);
        char c_out[20];
        generate_name(i + 10, c_out);
        char win_out[20];
        generate_name(i + 20, win_out);
        char cp_out[20];
        generate_name(i + 30, cp_out);
        printf("|%10d|%10lld|%10lld|%10lld|\n", i * FILE_PART_SIZE, copy_c(in, c_out) / 10,
               copy_windows(in, win_out) /10,
               windows_copyfile(in, cp_out) / 10);
    }
    return 0;
}