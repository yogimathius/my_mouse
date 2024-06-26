#ifndef __MATRIX_H_
#define __MATRIX_H_

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <fcntl.h> 
#include <unistd.h>
#include <sys/stat.h>
#include <stdbool.h>

#define SIZE 16
#define __MatrixClass_self_alignement 0xC0

struct Matrix {
    ssize_t size;
    char* header;
    char* buffer;
    char** matrix;
    int rows;
    int cols;
    char full;
    char empty;
    char path;
    char start;
    char end;
    int (*read)(const char* filename);
    int (*get_size)();
    void (*alloc)();
    int (*min_distance)();
    void (*debug)();
    void (*print)();
    void (*free)();
    bool (*validate_map)();
};


extern const struct MatrixClass {
    struct Matrix(*new)();
} Matrix;

#endif