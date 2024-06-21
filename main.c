#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

const float EPSILON = 0.00001f;

const float LEARNING_RATE = 0.01f;
const int EPOCHS = 10000;

const int TRAINING_SET_SIZE = 1000;

typedef struct Vector {
    size_t size;
    float *data;
} Vector;

Vector make_vector(size_t size) {
    float *data = malloc(size * sizeof(float));
    if (data == NULL) {
        printf("Failed allocation\n");
    }
    return (Vector){ .size = size, .data = data };
}

Vector apply_vector(Vector vector, float (*f)(float)) {
    Vector out_vector = make_vector(vector.size);
    for (int i = 0; i < vector.size; i++) {
        out_vector.data[i] = f(vector.data[i]);
    }
    return out_vector;
}

Vector multiply_vector_scalar(Vector vector, float scalar) {
    Vector out_vector = make_vector(vector.size);
    for (int i = 0; i < vector.size; i++) {
        out_vector.data[i] = vector.data[i] * scalar;
    }
    return out_vector;
}

Vector multiply_vector_vector(Vector vector1, Vector vector2) {
    assert(vector1.size == vector2.size);

    Vector out_vector = make_vector(vector1.size);
    for (int i = 0; i < vector1.size; i++) {
        out_vector.data[i] = vector1.data[i] * vector2.data[i];
    }
    return out_vector;
}

float mean_vector(Vector vector) {
    assert(vector.size != 0);

    float mean = 0;
    for (int i = 0; i < vector.size; i++) {
        mean += vector.data[i];
    }
    mean /= vector.size;

    return mean;
}

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

int main() {
    Vector training_inputs = make_vector(TRAINING_SET_SIZE);

    for (int i = 0; i < TRAINING_SET_SIZE; i++) {
        training_inputs.data[i] = (float)rand() / RAND_MAX;
    }

    Vector training_outputs = make_vector(TRAINING_SET_SIZE);

    for (int i = 0; i < TRAINING_SET_SIZE; i++) {
        training_outputs.data[i] = model_function(training_inputs.data[i]);
    }

    float node_weight = (float)rand() / RAND_MAX;
    float node_bias = (float)rand() / RAND_MAX;

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
