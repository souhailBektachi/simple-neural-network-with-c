#pragma once

#include <math.h>
#include "matrix.h"
// activation functions
double_t sigmoid(double_t x);

double_t sigmoid_prime(double_t x);
matrix *sigmoid_prime_matrix(matrix *m);
matrix *relu_prime_matrix(matrix *m);
matrix *softmax(matrix *m);
double_t Relu(double_t x);