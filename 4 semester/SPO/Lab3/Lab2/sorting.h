//
// Объявление функций для сортировки
//

#ifndef LAB2_SORTING_H
#define LAB2_SORTING_H

#include <stddef.h>
/*
 * Пирамидальная сортировка (2-куча)
 * Сортирует массив array размера arrSize
 * ипользуя для сравнения записей функцию compare
 */
template <class T>
void __declspec(dllexport) heapSort(T *array, long arrSize, int compare(T , T ));

#include "sort_util.cpp"

#endif //LAB2_SORTING_H
