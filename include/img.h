#pragma once
#include "matrix.h"

// image struct
typedef struct
{
    matrix *data;
    int label;
} image;

// image functions
image **csv_to_image(char *path, int num_of_images);
void image_print(image *img);
void image_free(image *img);
