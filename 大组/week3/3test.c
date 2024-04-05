#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "1function_definitions.c"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// 定义排序函数
void insert_sort(int arr[], int n);
void merge_sort(int arr[], int low, int high);
void quick_sort(int arr[], int low, int high);
void count_sort(int arr[], int n);
void radix_count_sort(int arr[], int n);

// 生成随机数组
void generate_random_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000; // 生成 0 到 999 之间的随机数
    }
}

// 定义测试排序函数性能的函数
void test_sorting_performance(int size, int num_tests) {
    // 计时器
    clock_t start_time, end_time;
    double total_time_insert = 0.0;
    double total_time_merge = 0.0;
    double total_time_quick = 0.0;
    double total_time_count = 0.0;
    double total_time_radix = 0.0;

    // 重复进行测试
    for (int test = 0; test < num_tests; test++) {
        int *arr_insert = (int *)malloc(size * sizeof(int));
        int *arr_merge = (int *)malloc(size * sizeof(int));
        int *arr_quick = (int *)malloc(size * sizeof(int));
        int *arr_count = (int *)malloc(size * sizeof(int));
        int *arr_radix = (int *)malloc(size * sizeof(int));

        // 生成随机数组
        generate_random_array(arr_insert, size);
        memcpy(arr_merge, arr_insert, size * sizeof(int));
        memcpy(arr_quick, arr_insert, size * sizeof(int));
        memcpy(arr_count, arr_insert, size * sizeof(int));
        memcpy(arr_radix, arr_insert, size * sizeof(int));

        // 记录排序开始时间
        start_time = clock();

        // 执行排序算法
        insert_sort(arr_insert, size);

        // 记录排序结束时间
        end_time = clock();

        // 计算排序时间
        double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        total_time_insert += elapsed_time;

        // 执行归并排序算法
        start_time = clock();
        merge_sort(arr_merge, 0, size - 1);
        end_time = clock();
        elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        total_time_merge += elapsed_time;

        // 执行快速排序算法
        start_time = clock();
        quick_sort(arr_quick, 0, size - 1);
        end_time = clock();
        elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        total_time_quick += elapsed_time;

        // 执行计数排序算法
        start_time = clock();
        count_sort(arr_count, size);
        end_time = clock();
        elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        total_time_count += elapsed_time;

        // 执行基数计数排序算法
        start_time = clock();
        radix_count_sort(arr_radix, size);
        end_time = clock();
        elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        total_time_radix += elapsed_time;

        // 释放数组内存
        free(arr_insert);
        free(arr_merge);
        free(arr_quick);
        free(arr_count);
        free(arr_radix);
    }

    // 计算平均排序时间
    double average_time_insert = total_time_insert / num_tests;
    double average_time_merge = total_time_merge / num_tests;
    double average_time_quick = total_time_quick / num_tests;
    double average_time_count = total_time_count / num_tests;
    double average_time_radix = total_time_radix / num_tests;

    // 打印排序结果
    printf("Size: %d, Tests: %d\n", size, num_tests);
    printf("InserSort Average Time: %.6f seconds\n", average_time_insert);
    printf("MergeSort Average Time: %.6f seconds\n", average_time_merge);
    printf("QuickSort Average Time: %.6f seconds\n", average_time_quick);
    printf("CountSort Average Time: %.6f seconds\n", average_time_count);
    printf("RadixSort Average Time: %.6f seconds\n", average_time_radix);
}

int main() {
    // 设置随机种子
    srand(time(NULL));

    // 测试排序算法的性能
    test_sorting_performance(100, 100000);  // 测试 100 个数据的排序性能，重复 100000 次

    return 0;
}
