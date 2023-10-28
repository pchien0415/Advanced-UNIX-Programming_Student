#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Custom structure to represent memory-based file
struct MemFile {
    char* data;     // Data buffer
    size_t size;    // Size of the data
    size_t pos;     // Current position
};

// Custom read function for fmemopen
int mem_read(void *cookie, char *buf, int size) {
    struct MemFile *mf = (struct MemFile *)cookie;
    if (mf->pos >= mf->size) {
        return 0;  // EOF
    }
  
    size_t bytes_to_read = size;
    if (mf->pos + size > mf->size) {
        bytes_to_read = mf->size - mf->pos;
    }
    
    memcpy(buf, mf->data + mf->pos, bytes_to_read);
    mf->pos += bytes_to_read;
    
    return (int)bytes_to_read;
}

// Custom write function for fmemopen
int mem_write(void *cookie, const char *buf, int size) {
    struct MemFile *mf = (struct MemFile *)cookie;
    
    // Resize the buffer if necessary
    if (mf->pos + size > mf->size) {
        size_t new_size = (mf->pos + size) ; // You can adjust this as needed
        char* new_data = realloc(mf->data, new_size);
        if (!new_data) {
            return -1;  // Error
        }
        mf->data = new_data;
        mf->size = new_size;
    }
    
    // Copy data to the buffer
    memcpy(mf->data + mf->pos, buf, size);
    mf->pos += size;
    
    return (int)size;
}

// Custom seek function for fmemopen
fpos_t mem_seek(void *cookie, fpos_t offset, int whence) {
    struct MemFile *mf = (struct MemFile *)cookie;
    
    if (whence == SEEK_SET) {
        mf->pos = (size_t) offset;
    } else if (whence == SEEK_CUR) {
        mf->pos += (size_t)offset;
    } else if (whence == SEEK_END) {
        mf->pos = mf->size + (size_t)offset;
    } else {
        return -1;  // Error
    }
    
    return 0;  // Success
}

// Custom close function for fmemopen
int mem_close(void *cookie) {
    struct MemFile *mf = (struct MemFile *)cookie;
    free(mf->data); // Free the data buffer
    free(mf);       // Free the MemFile structure
    return 0;       // Success
}

int main() {
    // Initialize a memory-based file
    struct MemFile *memFile = (struct MemFile *)malloc(sizeof(struct MemFile));
    memFile->data = (char *)malloc(512);  // Initial buffer size
    memFile->size = 512;
    memFile->pos = 0;

    // Create a FILE stream using funopen
    FILE *file = funopen(memFile, mem_read, mem_write, mem_seek, mem_close);

    
    fprintf(file, "hello, world");

    
    fseek(file, 7, SEEK_SET);

    
    char * Buffer[512];
    fread(Buffer, 1, 6, file);
    printf("%s\n", Buffer);
    fseek( file,0,SEEK_SET ) ;
    fread(Buffer,1,512,file ) ;
    printf("%s\n",Buffer) ; 
    // Task 4: Close the file stream correctly
    fclose(file);

    return 0;
}