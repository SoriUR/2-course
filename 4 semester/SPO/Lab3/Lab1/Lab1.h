#ifndef LAB1_H
#define LAB1_H
#include "windows.h"
#ifdef __cplusplus
extern "C" {
#endif

#ifdef LAB1_DLL
#define LAB1_DLL_API __declspec(dllexport)
#else
#define LAB1_DLL_API __declspec(dllimport)
#endif
void LAB1_DLL_API generate_name(int i, char *buf);
long long int LAB1_DLL_API windows_copyfile(char *in_path, char *out_path);
long long LAB1_DLL_API copy_windows(char *in_path, char *out_path);
long long LAB1_DLL_API copy_c(char *in_path, char *out_path);
long long LAB1_DLL_API get_diff(SYSTEMTIME begin, SYSTEMTIME end);
void LAB1_DLL_API generate_files(int count, int init_size, int step);

#ifdef __cplusplus
}
#endif

#endif  // EXAMPLE_DLL_H