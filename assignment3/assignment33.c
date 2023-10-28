#include <stdio.h>
#include <string.h>

// 定义一个内存结构，用于存储数据
struct MemoryBuffer {
    char data[100]; // 假设最多存储100个字符
    size_t position; // 当前位置
};

// 自定义的读操作函数
int ReadMemory(void* cookie, char* buf, int size) {
    struct MemoryBuffer* mem = (struct MemoryBuffer*)cookie;
    int bytesToRead = size;
    
    if (mem->position + size > sizeof(mem->data)) {
        bytesToRead = sizeof(mem->data) - mem->position;
    }
    
    memcpy(buf, mem->data + mem->position, bytesToRead);
    mem->position += bytesToRead;
    
    return bytesToRead;
}

// 自定义的写操作函数
int WriteMemory(void* cookie, const char* buf, int size) {
    struct MemoryBuffer* mem = (struct MemoryBuffer*)cookie;
    int bytesToWrite = size;
    
    if (mem->position + size > sizeof(mem->data)) {
        bytesToWrite = sizeof(mem->data) - mem->position;
    }
    
    memcpy(mem->data + mem->position, buf, bytesToWrite);
    mem->position += bytesToWrite;
    
    return bytesToWrite;
}

// 自定义的定位函数
fpos_t SeekMemory(void* cookie, fpos_t offset, int whence) {
    struct MemoryBuffer* mem = (struct MemoryBuffer*)cookie;
    fpos_t newPosition;
    
    if (whence == SEEK_SET) {
        newPosition = offset;
    } else if (whence == SEEK_CUR) {
        newPosition = mem->position + offset;
    } else if (whence == SEEK_END) {
        newPosition = sizeof(mem->data) - offset;
    } else {
        return -1;
    }
    
    if (newPosition < 0 || newPosition > sizeof(mem->data)) {
        return -1;
    }
    
    mem->position = (size_t)newPosition;
    return newPosition;
}

// 自定义的关闭函数
int CloseMemory(void* cookie) {
    return 0; // 关闭成功
}

int main() {
    struct MemoryBuffer memory;
    memset(&memory, 0, sizeof(memory));
    
    // 使用funopen创建文件流
    FILE* stream = funopen(&memory, ReadMemory, WriteMemory, SeekMemory, CloseMemory);
    
    // 写入 "hello, world" 到文件流
    fprintf(stream, "hello, world");
    
    // 定位到 "world" 并打印
    fseek(stream, 7, SEEK_SET);
    char word[100];
    fread(word, 1, 6, stream);
    printf("%s\n", word);
    
    // 打印整个句子 "hello, world"
    fseek(stream, 0, SEEK_SET);
    fread(word, 1, 512, stream);
    printf("%s\n", word);
    
    // 关闭文件流
    fclose(stream);
    
    return 0;
}
