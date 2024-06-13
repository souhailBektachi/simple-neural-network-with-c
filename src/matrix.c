#include "matrix.h"
#include <sys/stat.h>
int check_dimensions(matrix *a, matrix *b)
{
    if (a->rows == b->rows && a->cols == b->cols)
        return 1;
    return 0;
}
bool matrix_isnull(matrix *m)
{

    if (m == NULL)
    {
        printf("Matrix is NULL\n");
        return true;
    }
    return false;
}
matrix *matrix_init(int rows, int cols)
{
    matrix *m = malloc(sizeof(matrix));
    m->rows = rows;
    m->cols = cols;
    m->data = malloc(rows * sizeof(double_t *));
    for (int i = 0; i < rows; i++)
    {
        m->data[i] = malloc(cols * sizeof(double_t));
    }
    return m;
}

void matrix_free(matrix *m)
{

    for (int i = 0; i < m->rows; i++)
    {

        free(m->data[i]);
    }
    free(m->data);
    free(m);
    m = NULL;
}
void matrix_print(matrix *m)
{
    if (matrix_isnull(m))
        return;
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            printf("%f ", m->data[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
double_t uniform_destribution(double_t min, double_t max)
{
    double_t difference = max - min;
    int scale = 10000;
    int scaled_difference = (int)(difference * scale);
    return min + (1.0 * (rand() % scaled_difference) / scale);
}
void matrix_randomize(matrix *m, int n)
{
    if (matrix_isnull(m))
        return;
    double_t min = -1.0 / sqrt(n);
    double_t max = 1.0 / sqrt(n);
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            m->data[i][j] = uniform_destribution(min, max);
        }
    }
}
matrix *matrix_add(matrix *a, matrix *b)
{
    if (!check_dimensions(a, b))
    {
        exit(1);
    }
    matrix *m = matrix_init(a->rows, a->cols);
    for (int i = 0; i < a->rows; i++)
    {
        for (int j = 0; j < b->cols; j++)
        {
            m->data[i][j] = a->data[i][j] + b->data[i][j];
        }
    }
    return m;
}
matrix *matrix_sub(matrix *a, matrix *b)
{
    if (!check_dimensions(a, b))
    {
        exit(1);
    }
    matrix *m = matrix_init(a->rows, a->cols);
    for (int i = 0; i < a->rows; i++)
    {
        for (int j = 0; j < b->cols; j++)
        {
            m->data[i][j] = a->data[i][j] - b->data[i][j];
        }
    }
    return m;
}
matrix *matrix_mul(matrix *a, matrix *b)
{

    if (!check_dimensions(a, b))
    {
        exit(1);
    }
    matrix *m = matrix_init(a->rows, a->cols);
    for (int i = 0; i < a->rows; i++)
    {
        for (int j = 0; j < b->cols; j++)
        {
            m->data[i][j] = a->data[i][j] * b->data[i][j];
        }
    }
    return m;
}
matrix *matrix_copy(matrix *m)
{
    matrix *copy = matrix_init(m->rows, m->cols);
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            copy->data[i][j] = m->data[i][j];
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
    matrix *m = matrix_init(rows, cols);
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
void save_matrix(matrix *m, const char *filename)
{

    char *folder = "models/";
    char *path = malloc(strlen(folder) + strlen(filename) + 1);
    strcpy(path, folder);
    strcat(path, filename);
    // if windows
    MKDIR(folder);

    FILE *file = fopen(path, "w");
    fprintf(file, "%d\n", m->rows);
    fprintf(file, "%d\n", m->cols);
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            fprintf(file, "%.6f\n", m->data[i][j]);
        }
    }
    printf("Successfully saved matrix to %s\n", filename);
    free(path);
    fclose(file);
}
void matrix_fill(matrix *m, double_t val)
{
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            m->data[i][j] = val;
        }
    }
}
int matrix_argmax(matrix *m)
{
    if (matrix_isnull(m))
        return -1;
    double_t max_score = 0;
    int max_idx = 0;
    for (int i = 0; i < m->rows; i++)
    {
        if (m->data[i][0] > max_score)
        {
            max_score = m->data[i][0];
            max_idx = i;
        }
    }
    return max_idx;
}
matrix *matrix_flatten(matrix *m, int axis)
{
    matrix *mat;
    if (axis == 0)
    {
        mat = matrix_init(m->rows * m->cols, 1);
    }
    else if (axis == 1)
    {
        mat = matrix_init(1, m->rows * m->cols);
    }
    else
    {
        printf("Argument to matrix_flatten must be 0 or 1");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            if (axis == 0)
                mat->data[i * m->cols + j][0] = m->data[i][j];
            else if (axis == 1)
                mat->data[0][i * m->cols + j] = m->data[i][j];
        }
    }
    return mat;
}

matrix *dot(matrix *a, matrix *b)
{

    if (!(a->cols == b->rows))
    {
        exit(1);
    }
    matrix *m = matrix_init(a->rows, b->cols);
    for (int i = 0; i < a->rows; i++)
    {
        for (int j = 0; j < b->cols; j++)
        {
            double_t sum = 0;
            for (int k = 0; k < b->rows; k++)
            {
                sum += a->data[i][k] * b->data[k][j];
            }
            m->data[i][j] = sum;
        }
    }
    return m;
}
matrix *apply(matrix *m, double_t (*func)(double_t))
{
    if (matrix_isnull(m))
        return NULL;
    matrix *result;
    result = matrix_copy(m);
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            result->data[i][j] = func(m->data[i][j]);
        }
    }

    return result;
}
matrix *scalar(matrix *m, double_t scalar)
{
    matrix *mat = matrix_copy(m);
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            mat->data[i][j] *= scalar;
        }
    }
    return mat;
}
matrix *add_scalar(matrix *m, double_t scalar)
{
    matrix *result = matrix_copy(m);
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            result->data[i][j] = m->data[i][j] + scalar;
        }
    }
    return result;
}
matrix *transpose(matrix *m)
{
    matrix *result = matrix_init(m->cols, m->rows);
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            result->data[j][i] = m->data[i][j];
        }
    }
    return result;
}