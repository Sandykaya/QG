#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_test_data(int length, int min_value, int max_value, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Unable to open file %s for writing.\n", filename);
        return;
    }

    srand(time(NULL));  // 使用当前时间作为随机种子

    for (int i = 0; i < length; i++) {
        int data = rand() % (max_value - min_value + 1) + min_value;
        fprintf(file, "%d\n", data);
    }

    fclose(file);
    printf("Generated test data saved to %s.\n", filename);
}

int main() {
    int length = 20;          // 数据长度
    int min_value = 0;          // 数据最小值
    int max_value = 100;        // 数据最大值
    const char *filename = "test_data.txt";  // 文件名

    generate_test_data(length, min_value, max_value, filename);

    return 0;
}
