#pragma once
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#define MAX 100
// matrix struct

typedef struct
{
    float **data;
    int rows;
    int cols;
} matrix;

bool matrix_isnull(matrix **m);
// matrix functions
void matrix_init(matrix **m, int rows, int cols);
void matrix_free(matrix **m);
void matrix_print(matrix **m);
void matrix_randomize(matrix **m);
matrix *matrix_copy(matrix **m);
matrix *load_matrix(const char *filename);
void save_matrix(matrix **m, const char *filename);
int matrix_argmax(matrix **m);
matrix *matrix_flatten(matrix **m, int axis);

void matrix_add(matrix **m, matrix **a, matrix **b);
void matrix_sub(matrix **m, matrix **a, matrix **b);
void matrix_mul(matrix **m, matrix **a, matrix **b);
void dot(matrix **m, matrix **a, matrix **b);
void apply(matrix **m, float (*func)(float));
matrix *scalar(matrix **m, float scalar);
matrix *add_scalar(matrix **m, float scalar);
matrix *transpose(matrix **m);