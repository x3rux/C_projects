#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>

typedef struct{
    size_t rows;
    size_t cols;
    float *data;
}Matrix;

Matrix* matrix_allocate(size_t rows, size_t cols);
void matrix_free(Matrix* m);
void matrix_print(Matrix* m);

#endif

