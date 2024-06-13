#pragma once
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#define MAX 100
#ifdef _WIN32
#include <direct.h>
#define MKDIR(folder) mkdir(folder)
#else
#include <sys/stat.h>
#include <sys/types.h>
#define MKDIR(folder) mkdir(folder, 0777)
#endif
// matrix struct

typedef struct
{
    double_t **data;
    int rows;
    int cols;
} matrix;

bool matrix_isnull(matrix *m);
// matrix functions
matrix *matrix_init(int rows, int cols);
void matrix_free(matrix *m);
void matrix_print(matrix *m);
void matrix_randomize(matrix *m, int n);
void matrix_fill(matrix *m, double_t val);
matrix *matrix_copy(matrix *m);
matrix *load_matrix(const char *filename);
void save_matrix(matrix *m, const char *filename);
int matrix_argmax(matrix *m);
matrix *matrix_flatten(matrix *m, int axis);

matrix *matrix_add(matrix *a, matrix *b);
matrix *matrix_sub(matrix *a, matrix *b);
matrix *matrix_mul(matrix *a, matrix *b);
matrix *dot(matrix *a, matrix *b);
matrix *apply(matrix *m, double_t (*func)(double_t));
matrix *scalar(matrix *m, double_t scalar);
matrix *add_scalar(matrix *m, double_t scalar);
matrix *transpose(matrix *m);