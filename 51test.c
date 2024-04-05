#include <stdio.h>

void sort_012(int arr[], int n) {
    int p0 = 0, p2 = n - 1, curr = 0;

    while (curr <= p2) {
        if (arr[curr] == 0) {
            // 将0交换到前面
            int temp = arr[curr];
            arr[curr] = arr[p0];
            arr[p0] = temp;
            p0++;
            curr++;
        } else if (arr[curr] == 2) {
            // 将2交换到后面
            int temp = arr[curr];
            arr[curr] = arr[p2];
            arr[p2] = temp;
            p2--;
        } else {
            // 对于1，直接跳过
            curr++;
        }
    }
}

int main() {
    int arr[] = {1, 2, 1, 0, 2, 0, 0};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Origin array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    sort_012(arr, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
