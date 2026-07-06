#include <stdio.h>
#include <stdlib.h>
#include "../include/Matrix.h"

Matrix* matrix_allocate(size_t rows, size_t cols){
    Matrix* m = malloc(sizeof(Matrix));
    if(m == NULL) return NULL;

    m->rows = rows;
    m->cols = cols;

    m->data = calloc(rows*cols, sizeof(float));
    if(m->data == NULL){
        free(m);
        return NULL;
    }

    return m;
}

void matrix_free(Matrix *m){
    if(m == NULL) return; //because should not free a null pointer

    free(m->data);
    free(m);
}

void matrix_print(Matrix *m){
    for (size_t i = 0; i < m->rows; i++) {
        for (size_t j = 0; j < m->cols; j++) {
            printf(" %.2f ", m->data[m->cols * i + j]);
        }
        printf("\n");
    }
}