#include "matrix.h"

bool matrix_isnull(matrix **m)
{

    if (m == NULL)
    {
        printf("Matrix is NULL\n");
        return true;
    }
    return false;
}
void matrix_init(matrix **m, int rows, int cols)
{
    (*m) = (matrix *)malloc(sizeof(matrix));
    (*m)->rows = rows;
    (*m)->cols = cols;
    (*m)->data = (float **)malloc(rows * sizeof(float *));
    for (int i = 0; i < rows; i++)
    {
        (*m)->data[i] = (float *)malloc(cols * sizeof(float));
    }
}

void matrix_free(matrix **m)
{
    if (matrix_isnull(m))
        return;
    for (int i = 0; i < (*m)->rows; i++)
    {
        free((*m)->data[i]);
    }
    free((*m)->data);
    free(*m);
}
void matrix_print(matrix **m)
{
    if (matrix_isnull(m))
        return;
    for (int i = 0; i < (*m)->rows; i++)
    {
        for (int j = 0; j < (*m)->cols; j++)
        {
            printf("%f ", (*m)->data[i][j]);
        }
        printf("\n");
    }
}
void matrix_randomize(matrix **m)
{
    if (matrix_isnull(m))
        return;
    for (int i = 0; i < (*m)->rows; i++)
    {
        for (int j = 0; j < (*m)->cols; j++)
        {
            (*m)->data[i][j] = (float)rand() / RAND_MAX;
        }
    }
}
void matrix_add(matrix **m, matrix **a, matrix **b)
{

    if (matrix_isnull(m))
        return;
    for (int i = 0; i < (*m)->rows; i++)
    {
        for (int j = 0; j < (*m)->cols; j++)
        {
            (*m)->data[i][j] = (*a)->data[i][j] + (*b)->data[i][j];
        }
    }
}
void matrix_sub(matrix **m, matrix **a, matrix **b)
{
    if (matrix_isnull(m))
        return;
    for (int i = 0; i < (*m)->rows; i++)
    {
        for (int j = 0; j < (*m)->cols; j++)
        {
            (*m)->data[i][j] = (*a)->data[i][j] - (*b)->data[i][j];
        }
    }
}
void matrix_mul(matrix **m, matrix **a, matrix **b)
{
    if (matrix_isnull(m))
        return;
    for (int i = 0; i < (*m)->rows; i++)
    {
        for (int j = 0; j < (*m)->cols; j++)
        {
            (*m)->data[i][j] = 0;
            for (int k = 0; k < (*a)->cols; k++)
            {
                (*m)->data[i][j] += (*a)->data[i][k] * (*b)->data[k][j];
            }
        }
    }
}
matrix *matrix_copy(matrix **m)
{
    matrix *copy;
    matrix_init(&copy, (*m)->rows, (*m)->cols);
    for (int i = 0; i < (*m)->rows; i++)
    {
        for (int j = 0; j < (*m)->cols; j++)
        {
            copy->data[i][j] = (*m)->data[i][j];
        }
    }
    return copy;
}
matrix *load_matrix(const char *filename)
{
    FILE *file = fopen(filename, "r");
    char entry[MAX];
    fgets(entry, MAX, file);
    int rows = atoi(entry);
    fgets(entry, MAX, file);
    int cols = atoi(entry);
    matrix *m;
    matrix_init(&m, rows, cols);
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            fgets(entry, MAX, file);
            m->data[i][j] = strtod(entry, NULL);
        }
    }
    printf("Sucessfully loaded matrix from %s\n", filename);
    fclose(file);
    return m;
}
void save_matrix(matrix **m, const char *filename)
{
    matrix *matrix = *m;
    FILE *file = fopen(filename, "w");
    fprintf(file, "%d\n", matrix->rows);
    fprintf(file, "%d\n", matrix->cols);
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->cols; j++)
        {
            fprintf(file, "%.6f\n", matrix->data[i][j]);
        }
    }
    printf("Successfully saved matrix to %s\n", filename);
    fclose(file);
}
int matrix_argmax(matrix **m)
{
    if (matrix_isnull(m))
        return -1;
    int max_index = 0;
    float max = (*m)->data[0][0];
    for (int i = 0; i < (*m)->rows; i++)
    {
        for (int j = 0; j < (*m)->cols; j++)
        {
            if ((*m)->data[i][j] > max)
            {
                max = (*m)->data[i][j];
                max_index = i;
            }
        }
    }
    return max_index;
}
matrix *matrix_flatten(matrix **m, int axis)
{
    if (matrix_isnull(m))
        return NULL;
    matrix *flattened;
    if (axis == 0)
    {
        matrix_init(&flattened, (*m)->rows * (*m)->cols, 1);
        for (int i = 0; i < (*m)->rows; i++)
        {
            for (int j = 0; j < (*m)->cols; j++)
            {
                flattened->data[i * (*m)->cols + j][0] = (*m)->data[i][j];
            }
        }
    }
    else
    {
        matrix_init(&flattened, 1, (*m)->rows * (*m)->cols);
        for (int i = 0; i < (*m)->rows; i++)
        {
            for (int j = 0; j < (*m)->cols; j++)
            {
                flattened->data[0][i * (*m)->cols + j] = (*m)->data[i][j];
            }
        }
    }
    return flattened;
}

void dot(matrix **m, matrix **a, matrix **b)
{
    if (matrix_isnull(m))
        return;
    matrix *m1 = *a;
    matrix *m2 = *b;

    if (m1->cols == m2->rows)
    {
        (*m) = matrix_create(m1->rows, m2->cols);
        for (int i = 0; i < m1->rows; i++)
        {
            for (int j = 0; j < m2->cols; j++)
            {
                double sum = 0;
                for (int k = 0; k < m2->rows; k++)
                {
                    sum += m1->data[i][k] * m2->data[k][j];
                }
                (*m)->data[i][j] = sum;
            }
        }
    }
    else
    {
        printf("Dimension mistmatch dot: %dx%d %dx%d\n", m1->rows, m1->cols, m2->rows, m2->cols);
        exit(1);
    }
}
void apply(matrix **m, float (*func)(float))
{
    if (matrix_isnull(m))
        return;
    m = matrix_copy(m);
    for (int i = 0; i < (*m)->rows; i++)
    {
        for (int j = 0; j < (*m)->cols; j++)
        {
            (*m)->data[i][j] = func((*m)->data[i][j]);
        }
    }
}
matrix *scalar(matrix **m, float scalar)
{
    matrix *result = matrix_copy(m);
    for (int i = 0; i < (*m)->rows; i++)
    {
        for (int j = 0; j < (*m)->cols; j++)
        {
            result->data[i][j] = (*m)->data[i][j] * scalar;
        }
    }
    return result;
}
matrix *add_scalar(matrix **m, float scalar)
{
    matrix *result = matrix_copy(m);
    for (int i = 0; i < (*m)->rows; i++)
    {
        for (int j = 0; j < (*m)->cols; j++)
        {
            result->data[i][j] = (*m)->data[i][j] + scalar;
        }
    }
    return result;
}
matrix *transpose(matrix **m)
{
    matrix *result;
    matrix_init(&result, (*m)->cols, (*m)->rows);
    for (int i = 0; i < (*m)->rows; i++)
    {
        for (int j = 0; j < (*m)->cols; j++)
        {
            result->data[j][i] = (*m)->data[i][j];
        }
    }
    return result;
}