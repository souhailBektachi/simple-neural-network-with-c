#include "activationfunc.h"

double_t sigmoid(double_t x)
{
    return 1.0 / (1 + exp(-1 * x));
}
double_t sigmoid_prime(double_t x)
{
    return sigmoid(x) * (1 - sigmoid(x));
}
matrix *sigmoid_prime_matrix(matrix *m)
{

    matrix *ones, *result;
    ones = matrix_init(m->rows, 1);
    matrix_fill(ones, 1);
    result = matrix_sub(ones, m);
    result = matrix_mul(result, m);
    matrix_free(ones);
    return result;
}
matrix *softmax(matrix *m)
{
    double_t total = 0;
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            total += exp(m->data[i][j]);
        }
    }
    matrix *mat = matrix_init(m->rows, m->cols);
    for (int i = 0; i < mat->rows; i++)
    {
        for (int j = 0; j < mat->cols; j++)
        {
            mat->data[i][j] = exp(m->data[i][j]) / total;
        }
    }
    return mat;
}