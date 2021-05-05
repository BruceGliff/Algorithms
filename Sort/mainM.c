#include <stdio.h>

void sort(int * arr, int n, int id, int size) {
    int i = id;
    int j = n - 1 - id;
    int pivot = arr[n / 2];

    do {
        while (arr[i] < pivot) i += size;
        while (arr[j] > pivot) j -= size;
        if (i <= j) {
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i += size;
            j -= size;
        }
    } while (i <= j);

    if (j > 0)
        sort(arr, j + 1 + size, id, size);
    if (n > i)
        sort(arr + i, n - i - size, id, size);
}

int main() {
    int arr[] = {1, 48, 6, 481, 63879, 97, 4897, 3112, 3489, 7894684, 8616, 687};
    int const n = sizeof(arr) / sizeof(int);

    sort(arr, n, 0, 2);
    sort(arr, n, 1, 2);

    for (int i = 0; i != n; ++i) 
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}