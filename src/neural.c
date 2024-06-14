#include "neural.h"
neural *neural_init(int inputs, int hidden, int outputs, double_t learning_rate)
{
    neural *n = (neural *)malloc(sizeof(neural));
    n->inputs = inputs;
    n->hidden = hidden;
    n->outputs = outputs;
    n->learning_rate = learning_rate;

    n->weights_ih = matrix_init(hidden, inputs);
    n->weights_ho = matrix_init(outputs, hidden);
    matrix_randomize(n->weights_ih, hidden);
    matrix_randomize(n->weights_ho, outputs);
    return n;
}
void neural_free(neural *n)
{
    matrix_free(n->weights_ih);
    matrix_free(n->weights_ho);
    free(n);
}
void neural_train(neural *n, matrix *input, matrix *output)
{
    // feed forward
    matrix *hidden_inputs = dot(n->weights_ih, input);
    matrix *hidden_outputs = apply(hidden_inputs, sigmoid);
    matrix *output_inputs = dot(n->weights_ho, hidden_outputs);
    matrix *outputs = apply(output_inputs, sigmoid);

    // calculate error
    matrix *output_errors = matrix_sub(output, outputs);
    matrix *transposed = transpose(n->weights_ho);
    matrix *hidden_errors = dot(transposed, output_errors);
    matrix_free(transposed);

    // backpropagation
    matrix *gradients = sigmoid_prime_matrix(outputs);
    matrix *multiplied = matrix_mul(output_errors, gradients);
    transposed = transpose(hidden_outputs);
    matrix *doted = dot(multiplied, transposed);
    matrix *scaled = scalar(doted, n->learning_rate);
    matrix *added = matrix_add(n->weights_ho, scaled);
    matrix_free(n->weights_ho);
    n->weights_ho = added;
    // free matrix to reuse
    matrix_free(gradients);
    matrix_free(multiplied);
    matrix_free(transposed);
    matrix_free(doted);
    matrix_free(scaled);

    // hidden layer
    gradients = sigmoid_prime_matrix(hidden_outputs);
    multiplied = matrix_mul(hidden_errors, gradients);
    transposed = transpose(input);
    doted = dot(multiplied, transposed);
    scaled = scalar(doted, n->learning_rate);
    added = matrix_add(n->weights_ih, scaled);
    matrix_free(n->weights_ih);
    n->weights_ih = added;
    // free matrix
    matrix_free(gradients);
    matrix_free(multiplied);
    matrix_free(transposed);
    matrix_free(doted);
    matrix_free(scaled);
    matrix_free(hidden_inputs);
    matrix_free(hidden_outputs);
    matrix_free(output_inputs);
    matrix_free(outputs);
    matrix_free(output_errors);
    matrix_free(hidden_errors);
}

matrix *neural_predict(neural *n, matrix *input)
{
    matrix *hidden_inputs = dot(n->weights_ih, input);
    matrix *hidden_outputs = apply(hidden_inputs, sigmoid);
    matrix *output_inputs = dot(n->weights_ho, hidden_outputs);
    matrix *outputs = apply(output_inputs, sigmoid);
    matrix *result = softmax(outputs);
    matrix_free(hidden_inputs);
    matrix_free(hidden_outputs);
    matrix_free(output_inputs);
    matrix_free(outputs);
    return result;
}
matrix *neural_predict_image(neural *n, image *img)
{
    matrix *image_data = matrix_flatten(img->data, 0);
    matrix *result = neural_predict(n, image_data);
    matrix_free(image_data);
    return result;
}
double_t neural_accuracy(neural *nn, image **images, int n)
{
    int correct = 0;
    for (int i = 0; i < n; i++)
    {
        matrix *result = neural_predict_image(nn, images[i]);

        if (matrix_argmax(result) == images[i]->label)
        {
            correct++;
        }
        matrix_free(result);
    }
    printf("Correct: %d\n", correct);
    return 1.0 * correct / n;
}
void neural_train_batch_image(neural *n, image **images, int batch_size)
{
    for (int i = 0; i < batch_size; i++)
    {
        if (i % 100 == 0)
            printf("Training %d/%d\n", i, batch_size);
        matrix *input, *output;
        image *img = images[i];
        input = matrix_flatten(img->data, 0);
        output = matrix_init(10, 1);
        output->data[img->label][0] = 1;
        neural_train(n, input, output);

        matrix_free(input);
        matrix_free(output);
    }
}

void neural_save(neural *n, char *filename)
{
    char *folder = "models/";
    char *path = malloc(strlen(folder) + strlen(filename) + 1);
    strcpy(path, folder);
    strcat(path, filename);
    // create if not exist
    MKDIR(folder);

    FILE *file = fopen(path, "w");

    if (file == NULL)
    {
        printf("Could not open file %s", path);
        return;
    }

    fprintf(file, "%d\n", n->inputs);
    fprintf(file, "%d\n", n->hidden);
    fprintf(file, "%d\n", n->outputs);
    fprintf(file, "%f\n", n->learning_rate);
    save_matrix(n->weights_ih, "weights_ih");
    save_matrix(n->weights_ho, "weights_ho");
    free(path);
    fclose(file);
}
neural *neural_load(const char *filename)
{
    char *folder = "models/";
    char *path = malloc(strlen(folder) + strlen(filename) + 1);
    strcpy(path, folder);
    strcat(path, filename);
    FILE *file = fopen(path, "r");
    if (file == NULL)
    {
        printf("Could not open file %s", path);
        return NULL;
    }
    char entry[MAX];
    fgets(entry, MAX, file);
    int inputs = atoi(entry);
    fgets(entry, MAX, file);
    int hidden = atoi(entry);
    fgets(entry, MAX, file);
    int outputs = atoi(entry);
    fgets(entry, MAX, file);
    double_t learning_rate = atof(entry);
    neural *n = neural_init(inputs, hidden, outputs, learning_rate);
    strcpy(path, folder);
    strcat(path, "weights_ih");
    n->weights_ih = load_matrix(path);
    strcpy(path, folder);
    strcat(path, "weights_ho");
    n->weights_ho = load_matrix(path);
    free(path);
    fclose(file);
    return n;
}

void neural_print(neural *n)
{
    printf("Inputs: %d\n", n->inputs);
    printf("Hidden: %d\n", n->hidden);
    printf("Outputs: %d\n", n->outputs);
    printf("Learning rate: %f\n", n->learning_rate);
    printf("Weights ih:\n");
    matrix_print(n->weights_ih);
    printf("Weights ho:\n");
    matrix_print(n->weights_ho);
}
