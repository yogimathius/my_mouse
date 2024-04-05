#ifndef __MY_MOUSE_
#define __MY_MOUSE_

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <fcntl.h> 
#include <unistd.h>
#include <sys/stat.h>

#define HELP "Usage: ./my_mouse [file]\n"

#define SIZE 16
#define __MatrixClass_self_alignement 0xC0

struct Matrix {
    ssize_t size;
    char* buffer;
    int** matrix;
    int rows;
    int cols;
    int max_val;
    int max_row;
    int max_col;
    int (*read)(const char* filename);
    int (*get_size)();
    void (*alloc)();
    void (*build)();
    void (*debug)();
    void (*print)();
    void (*free)();
};


extern const struct MatrixClass {
    struct Matrix(*new)();
} Matrix;

int my_mouse(const char* file);

#endif