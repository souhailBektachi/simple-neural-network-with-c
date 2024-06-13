#pragma once

#include "matrix.h"
#include "img.h"
#include "activationfunc.h"
#include <sys/stat.h>

// neural struct
typedef struct
{
    int inputs;
    int hidden;
    int outputs;
    matrix *weights_ih;
    matrix *weights_ho;
    double_t learning_rate;

} neural;

// neural functions
neural *neural_init(int inputs, int hidden, int outputs, double_t learning_rate);
void neural_free(neural *n);
void neural_train(neural *n, matrix *input, matrix *output);
void neural_train_batch_image(neural *n, image **images, int batch_size);
matrix *neural_predict(neural *n, matrix *input);
matrix *neural_predict_image(neural *n, image *img);
double_t neural_accuracy(neural *nn, image **images, int n);
void neural_save(neural *n, char *filename);
neural *neural_load(const char *filename);
void neural_print(neural *n);
