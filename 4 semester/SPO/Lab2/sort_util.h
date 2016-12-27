//
// Created by User on 29.03.2016.
//

#ifndef LAB2_SORT_UTIL_H
#define LAB2_SORT_UTIL_H
template <class T>
void downHeap(T *array, int k, int heapSize, int (*compare)(T , T )) {
    T new_elem = array[k];
    int child;
    while (k <= heapSize / 2 - 1) {
        child = (2 * k + 1);
        if (child < heapSize - 1 && compare(array[child], array[child + 1]) < 0) {
            child++;
        }
        if (compare(new_elem, array[child]) >= 0) break;
        array[k] = array[child];
        k = child;
    }
    array[k] = new_elem;
}
template <class T>
void heapSort(T *array, long arrSize, int compare(T , T )) {
    long k = arrSize / 2 - 1;
    int i;
    for(i = k; i >= 0; i--)
        downHeap(array, i, arrSize, compare);
    T temp;
    for(i = arrSize - 1; i >= 0; i--) {
        temp = array[i];
        array[i] = array[0];
        array[0] = temp;
        downHeap(array, 0, i, compare);
    }
}
#endif //LAB2_SORT_UTIL_H
