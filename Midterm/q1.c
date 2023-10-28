#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_lines(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main(int argc, char *argv[]){
    FILE *input_file, *output_file;
    char *lines[100];
    char buffer[100];
    int num_lines = 0;
    input_file = fopen("source1.txt", "r"); // 打开文件以供读取
    output_file = fopen("sorted_source1.txt", "w");

    if (input_file == NULL) {
        perror("无法打开文件");
        return 1; // 打开文件失败
    }

    while (num_lines < 100 && fgets(buffer, sizeof(buffer), input_file) != NULL) {
        // 去除换行符
        buffer[strcspn(buffer, "\n")] = '\0';
        lines[num_lines] = strdup(buffer);
        num_lines++;
    }

    // 使用 qsort 对行进行排序
    qsort(lines, num_lines, sizeof(char *), compare_lines);

    // 输出排序后的行
    for (int i = 0; i < num_lines; i++) {
        fprintf(output_file, "%s\n", lines[i]);
        free(lines[i]); // 释放分配的内存
    }
    
    fclose(input_file); // 关闭文件
    fclose(output_file); // 关闭文件
    return 0;
}