#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "vector.c"

const float EPSILON = 0.00001f;

const float LEARNING_RATE = 0.01f;
const int EPOCHS = 10000;

const int TRAINING_SET_SIZE = 1000;

float relu(float value) {
    if (value > 0) {
        return value;
    } else {
        return 0;
    }
}

float relu_derivative(float value) {
    if (value > 0) {
        return 1.0f;
    } else {
        return 0.0f;
    }
}

float model_function(float input) {
    return 2.0f * input + 5.0f;
}

void populate_dataset(Vector *inputs, Vector *outputs) {
    assert(inputs->size == outputs->size);

    for (int i = 0; i < inputs->size; i++) {
        inputs->data[i] = (float)rand() / (float)RAND_MAX;
        outputs->data[i] = model_function(inputs->data[i]);
    }
}

int main() {
    Vector training_inputs = make_vector(TRAINING_SET_SIZE);
    Vector training_outputs = make_vector(TRAINING_SET_SIZE);
    populate_dataset(&training_inputs, &training_outputs);

    float node_weight = (float)rand() / (float)RAND_MAX;
    float node_bias = (float)rand() / (float)RAND_MAX;

    for (int epoch = 0; epoch < EPOCHS; epoch++) {
        Vector errors = make_vector(TRAINING_SET_SIZE);

        for (int i = 0; i < TRAINING_SET_SIZE; i++) {
            float node_input = training_inputs.data[i] * node_weight + node_bias;
            float node_output = relu(node_input);

            errors.data[i] = (training_outputs.data[i] - node_output);
        }

        float weight_gradient = -2.0f * mean_vector(multiply_vector_vector(apply_vector(training_inputs, relu_derivative), multiply_vector_vector(errors, training_inputs)));
        float   bias_gradient = -2.0f * mean_vector(multiply_vector_vector(apply_vector(training_inputs, relu_derivative), errors));

        node_weight -= LEARNING_RATE * weight_gradient;
        node_bias   -= LEARNING_RATE *   bias_gradient;

        float mse = mean_vector(multiply_vector_vector(errors, errors));

        printf("Epoch %d:\n", epoch);
        printf(" Weight is now %f\n", node_weight);
        printf(" Bias   is now %f\n", node_bias);
        printf(" MSE: %f\n", mse);

        if (fabsf(mse) <= EPSILON) {
            printf("\033[32mGreat success!\033[0m\n");
            exit(0);
        }
    }

    return 0;
}
