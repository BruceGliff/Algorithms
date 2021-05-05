#include <stdio.h>

void sort(int * arr, int n) {
    int i = 0;
    int j = n - 1;
    int pivot = arr[n / 2];

    do {
        while (arr[i] < pivot) ++i;
        while (arr[j] > pivot) --j;
        if (i <= j) {
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            ++i;
            --j;
        }
    } while (i <= j);

    if (j > 0)
        sort(arr, j + 1);
    if (n > i)
        sort(arr + i, n - i);
}

int main() {
    int arr[] = {1, 48, 6, 481, 63879, 974897, 3112, 3489, 7894684, 8616, 687};
    int const n = sizeof(arr) / sizeof(int);

    sort(arr, n);

    for (int i = 0; i != n; ++i) 
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}