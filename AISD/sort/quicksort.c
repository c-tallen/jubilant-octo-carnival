//
// Created by Krzysztof Wilczewski on 12/04/2023.
//
#include <stdio.h>

int divide(int *arr, int a, int b);
void quicksort(int *arr, int a, int b);

int main(void)
{
    int array[] = {2,3,3,5,2,1,5, 100, 23, 45, 12, 13, 14, 17};
    quicksort(array, 0, 13);
    for (int i = 0; i < 14; ++i) {
        printf("%d\t", array[i]);
    }
    return 0;
}
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int divide(int *arr, int a, int b)
{
    int pivot = arr[a + (b-a) / 2];
    swap(arr + a + (b-a) / 2, arr + b);
    int index = a;
    for (int i = a; i < b; ++i) {
        if (arr[i] <= pivot)
        {
            swap(arr + i, arr + index);
            index ++;
        }
    }
    swap(arr + b, arr + index);
    return index;
}

void quicksort(int *arr, int a, int b)
{
    if (a < b) {
        int pivot = divide(arr, a, b);
        quicksort(arr, a, pivot - 1);
        quicksort(arr, pivot + 1, b);
    }
}