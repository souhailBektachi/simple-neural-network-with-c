#include "matrix.h"
#include "time.h"
#include "img.h"
#include "neural.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int main()
{
    srand(clock());
    // training data
    int num_of_images = 10000;
    image **images = csv_to_image("dataset/data/mnist_train.csv", num_of_images);
    neural *nn = neural_init(784, 300, 10, 0.1);
    printf("Training...\n");
    neural_train_batch_image(nn, images, num_of_images);

    printf("Accuracy: %f\n", neural_accuracy(nn, images, num_of_images));
    neural_save(nn, "neural.model");
    neural_free(nn);
    for (int i = 0; i < num_of_images; i++)
    {
        image_free(images[i]);
    }
    free(images);
    // prediction
    // image **test_images = csv_to_image("dataset/data/mnist_test.csv", 10000);
    // neural *nn2 = neural_load("neural.model");
    // printf("Accuracy: %f\n", neural_accuracy(nn2, test_images, 10000));
    // neural_free(nn2);
    // for (int i = 0; i < 10000; i++)
    // {
    //     image_free(test_images[i]);
    // }
    // free(test_images);

    return 0;
}
