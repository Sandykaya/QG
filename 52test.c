#include <stdio.h>

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            // 交换 arr[i] 和 arr[j]
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    // 交换 arr[i+1] 和 arr[high]，以使得 pivot 元素位于正确的位置
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return (i + 1);
}

int kth_smallest(int arr[], int low, int high, int k) {
    // 如果 k 在有效范围内
    if (k > 0 && k <= high - low + 1) {
        // 在当前子数组中进行划分
        int pi = partition(arr, low, high);

        // 如果找到了第 k 小的元素
        if (pi - low == k - 1)
            return arr[pi];

        // 如果第 k 小的元素位于左侧子数组中
        if (pi - low > k - 1)
            return kth_smallest(arr, low, pi - 1, k);

        // 否则，第 k 小的元素位于右侧子数组中
        return kth_smallest(arr, pi + 1, high, k - pi + low - 1);
    }

    // 如果 k 不在有效范围内，返回 -1
    return -1;
}

int main() {
    int arr[] = {5, 2, 8, 4, 3, 7, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 3;

    int result = kth_smallest(arr, 0, n - 1, k);

    if (result != -1)
        printf("The %d-th smallest element is %d\n", k, result);
    else
        printf("Invalid input or array size is less than %d\n", k);

    return 0;
}
