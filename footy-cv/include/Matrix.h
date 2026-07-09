#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>

typedef struct{
    size_t rows;
    size_t cols;
    float *data;
}Matrix;

Matrix* matrix_allocate(size_t rows, size_t cols);
Matrix* matrix_dot(Matrix* a, Matrix* b);
Matrix* matrix_add(Matrix* a, Matrix* b);
Matrix* matrix_transpose(Matrix *m);
Matrix* matrix_subtract(Matrix *a, Matrix *b);
Matrix* matrix_clone(Matrix* m);
Matrix* matrix_multiply(Matrix* a, Matrix* b);//element by element multiplication


void matrix_scale(Matrix *m, float scalar);
void matrix_sigmoid_derivative(Matrix *m);
void matrix_sigmoid(Matrix* m);
void matrix_free(Matrix* m);
void matrix_print(Matrix* m);

#endif

