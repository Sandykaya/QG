#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "1function_definitions.c"

// 声明排序函数
extern void insert_sort(int arr[], int n);
extern void merge_sort(int arr[], int low, int high);
extern void quick_sort(int arr[], int low, int high);
extern void count_sort(int arr[], int n);
extern void radix_count_sort(int arr[], int n);

// 读取文件中的数据
int read_data_from_file(const char *filename, int **arr) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open file %s for reading.\n", filename);
        return -1;
    }

    // 获取文件中数据的数量
    int count = 0;
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        count++;
    }

    // 分配存储空间并读取数据
    *arr = (int *)malloc(count * sizeof(int));
    fseek(file, 0, SEEK_SET);
    int i = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        (*arr)[i++] = atoi(buffer);
    }

    fclose(file);
    return count;
}

// 输出数组元素
void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    const char *filename = "test_data.txt";  // 数据文件名

    // 读取数据
    int *arr;
    int size = read_data_from_file(filename, &arr);
    if (size <= 0) {
        return 1;
    }

    // 输出原始数据
    printf("Original data:\n");
    print_array(arr, size);

    // 使用不同的排序算法对数据进行排序并输出排序结果
    printf("\nSorted data using different sorting algorithms:\n");

    // 插入排序
    printf("Insertion sort:\n");
    insert_sort(arr, size);
    print_array(arr, size);

    // 归并排序
    printf("Merge sort:\n");
    merge_sort(arr, 0, size - 1);
    print_array(arr, size);

    // 快速排序
    printf("Quick sort:\n");
    quick_sort(arr, 0, size - 1);
    print_array(arr, size);

    // 计数排序
    printf("Count sort:\n");
    count_sort(arr, size);
    print_array(arr, size);

    // 基数计数排序
    printf("Radix count sort:\n");
    radix_count_sort(arr, size);
    print_array(arr, size);

    // 释放内存
    free(arr);

    return 0;
}
