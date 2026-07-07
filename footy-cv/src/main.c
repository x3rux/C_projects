#include <stdio.h>
#include <stdlib.h>
#include "../include/Matrix.h"

int main() {
    printf("--- Allocating Matrices ---\n");
    Matrix *a = matrix_allocate(2, 3);
    Matrix *b = matrix_allocate(3, 2);

    if (a == NULL || b == NULL) {
        printf("Failed to allocate base matrices.\n");
        return 1;
    }

    // Populate Matrix A with 1.0 to 6.0
    for (size_t i = 0; i < a->rows * a->cols; i++) {
      a->data[i] = (float)(i + 1);
    }

    // Populate Matrix B with 7.0 to 12.0
    for (size_t i = 0; i < b->rows * b->cols; i++) {
        b->data[i] = (float)(i + 7);
    }

    printf("Matrix A (2x3):\n");
    matrix_print(a);
    printf("\nMatrix B (3x2):\n");
    matrix_print(b);

    printf("\n--- Testing Dot Product ---\n");
    Matrix *c = matrix_dot(a, b);
    if (c != NULL) {
        printf("Matrix C = A dot B (2x2):\n");
        matrix_print(c);
    }

    printf("\n--- Testing Matrix Addition ---\n");
    // We add C to itself since they have identical dimensions
    Matrix *d = matrix_add(c, c);
    if (d != NULL) {
        printf("Matrix D = C + C:\n");
        matrix_print(d);
    }

    printf("\n--- Testing Sigmoid Activation ---\n");
    // We run sigmoid on A in-place
    matrix_sigmoid(a);
    printf("Matrix A after Sigmoid:\n");
    matrix_print(a);

    printf("\n--- Cleaning Up Memory ---\n");
    matrix_free(a);
    matrix_free(b);
    matrix_free(c);
    matrix_free(d);

    printf("All tests complete. Memory freed.\n");
    return 0;
}