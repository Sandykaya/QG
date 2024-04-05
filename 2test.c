#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "1function_definitions.c"

// 定义排序函数
void insert_sort(int arr[], int n);
void merge_sort(int arr[], int low, int high);
void quick_sort(int arr[], int low, int high);
void count_sort(int arr[], int n);
void radix_count_sort(int arr[], int n);

// 生成随机数组
void generate_random_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 1000000;  // 生成范围在 [0, 999999] 的随机数
    }
}

// 测试排序函数的性能
void test_sorting_performance(int size) {
    int *arr = (int *)malloc(size * sizeof(int));

    // 生成随机数组
    generate_random_array(arr, size);

    // 记录排序开始时间
    clock_t start_time, end_time;
    double elapsed_time;

    // 执行插入排序
    start_time = clock();
    insert_sort(arr, size);
    end_time = clock();
    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("InserSort-Size: %d, Elapsed-Time: %.6f seconds\n", size, elapsed_time);

    // 重新生成随机数组
    generate_random_array(arr, size);

    // 执行归并排序
    start_time = clock();
    merge_sort(arr, 0, size - 1);
    end_time = clock();
    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("MergeSort-Size: %d, Elapsed-Time: %.6f seconds\n", size, elapsed_time);

    // 重新生成随机数组
    generate_random_array(arr, size);

    // 执行快速排序
    start_time = clock();
    quick_sort(arr, 0, size - 1);
    end_time = clock();
    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("QuickSort-Size: %d, Elapsed-Time: %.6f seconds\n", size, elapsed_time);

    // 重新生成随机数组
    generate_random_array(arr, size);

    // 执行计数排序
    start_time = clock();
    count_sort(arr, size);
    end_time = clock();
    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("CountSort-Size: %d, Elapsed-Time: %.6f seconds\n", size, elapsed_time);

    // 重新生成随机数组
    generate_random_array(arr, size);

    // 执行基数计数排序
    start_time = clock();
    radix_count_sort(arr, size);
    end_time = clock();
    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("RadixSort-Size: %d, Elapsed-Time: %.6f seconds\n", size, elapsed_time);

    // 释放数组内存
    free(arr);
}

int main() {
    // 设置随机数种子
    srand(time(NULL));

    // 测试不同大小数据集的排序性能
    test_sorting_performance(10000);
    test_sorting_performance(50000);
    test_sorting_performance(200000);

    return 0;
}
