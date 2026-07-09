#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../include/Matrix.h"

void matrix_free(Matrix *m){
    if(m == NULL) return; //because should not free a null pointer

    free(m->data);
    free(m);
}

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

Matrix* matrix_dot(Matrix* a, Matrix* b){
    if(a == NULL || b == NULL) return NULL;
    if(a->cols != b->rows) {
        printf("ERROR: Incompatible matrices!\n");
        return NULL;
    }

    Matrix* c = matrix_allocate(a->rows, b->cols);
    if(c == NULL) return NULL;

    for (size_t i = 0; i < a->rows; i++) {
        for (size_t j = 0; j < b->cols; j++) {
            float sum = 0.0f;
            for (size_t k = 0; k < a->cols; k++) {
                size_t index_a = i * a->cols + k;
                size_t index_b = k * b->cols + j;
                
                sum += a->data[index_a] * b->data[index_b];
            }
            c->data[i * c->cols + j] = sum;
        }
    }
    return c;
}

Matrix* matrix_add(Matrix* a, Matrix* b){
    if(a == NULL || b == NULL) return NULL;
    if(a->rows != b->rows || a->cols != b->cols){
        printf("ERROR: Incompatible matrices!\n");
        return NULL;
    }

    Matrix* c = matrix_allocate(a->rows, a->cols);
    if(c == NULL) return NULL;

    for (size_t i = 0; i < c->rows * c->cols; i++) {
        c->data[i] = a->data[i] + b->data[i];
    }

    return c;
}

float sigmoid_helper(float f){
    return 1/(expf(-1 * f) + 1);
}

void matrix_sigmoid(Matrix *m){
    if(m == NULL) return;

    for (size_t i = 0; i < m->rows * m->cols; i++) {
        m->data[i] = sigmoid_helper(m->data[i]);
    }
}

Matrix* matrix_transpose(Matrix *m){
    Matrix* t = matrix_allocate(m->cols, m->rows);
    if(t == NULL) return NULL;

    for (size_t i = 0; i < m->rows; i++) {
        for (size_t j = 0; j < m->cols; j++) {
            t->data[j * t->cols + i] = m->data[i * m->cols + j];
        }
    }

    return t;
}

void matrix_scale(Matrix *m, float scalar){
    if(m == NULL) return;

    for (size_t i = 0; i < m->rows * m->cols; i++) {
        m->data[i] *= scalar;
    }
}

Matrix* matrix_subtract(Matrix* a, Matrix* b){
    if(a == NULL || b == NULL) return NULL;
    if(a->rows != b->rows || a->cols != b->cols){
        printf("ERROR: Incompatible matrices!\n");
        return NULL;
    }

    Matrix* c = matrix_allocate(a->rows, a->cols);
    if(c == NULL) return NULL;

    for (size_t i = 0; i < c->rows * c->cols; i++) {
        c->data[i] = a->data[i] - b->data[i];
    }

    return c;   
}

Matrix* matrix_clone(Matrix* m){
    if(m == NULL) return NULL;

    Matrix* c = matrix_allocate(m->rows, m->cols);
    if(c == NULL) return NULL;
    memcpy(c->data, m->data, c->rows * c->cols * sizeof(float));

    return c;
}

Matrix* matrix_multiply(Matrix* a, Matrix* b){// this is eleent by element multiplication
    if(a == NULL || b == NULL) return NULL;
    if(a->rows != b->rows || a->cols != b->cols){
        printf("ERROR: Incompatible matrices!\n");
        return NULL;
    }

    Matrix* c = matrix_allocate(a->rows, a->cols);
    if(c == NULL) return NULL;

    for (size_t i = 0; i < c->rows * c->cols; i++) {
        c->data[i] = a->data[i] * b->data[i];
    }

    return c;
}

void matrix_sigmoid_derivative(Matrix *m){
    if(m == NULL) return;

    for (size_t i = 0; i < m->rows * m->cols; i++) {
        m->data[i] = m->data[i] * (1.0f - m->data[i]);
    }
}

void matrix_print(Matrix *m){
    if(m == NULL) return;

    for (size_t i = 0; i < m->rows; i++) {
        for (size_t j = 0; j < m->cols; j++) {
            printf(" %.2f ", m->data[m->cols * i + j]);
        }
        printf("\n");
    }
}