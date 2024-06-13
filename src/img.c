#include "img.h"
#define MAXCHAR 10000
image **csv_to_image(char *path, int num_of_images)
{
    FILE *fp;
    image **imgs = malloc(num_of_images * sizeof(image *));
    char row[MAXCHAR];
    fp = fopen(path, "r");

    // Read the first line
    fgets(row, MAXCHAR, fp);
    int i = 0;
    while (feof(fp) != 1 && i < num_of_images)
    {
        imgs[i] = malloc(sizeof(image));

        int j = 0;
        fgets(row, MAXCHAR, fp);
        char *token = strtok(row, ",");
        imgs[i]->data = matrix_init(28, 28);
        while (token != NULL)
        {
            if (j == 0)
            {
                imgs[i]->label = atoi(token);
            }
            else
            {
                imgs[i]->data->data[(j - 1) / 28][(j - 1) % 28] = atoi(token) / 256.0;
            }
            token = strtok(NULL, ",");
            j++;
        }
        i++;
    }
    fclose(fp);
    return imgs;
}
void image_print(image *img)
{
    for (int i = 0; i < img->data->rows; i++)
    {
        for (int j = 0; j < img->data->cols; j++)
        {
            printf("%f ", img->data->data[i][j]);
        }
        printf("\n");
    }
    printf("Label: %d\n", img->label);
}
void image_free(image *img)
{
    matrix_free(img->data);
    free(img);
}
