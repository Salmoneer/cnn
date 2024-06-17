#include <stdio.h>
#include <stdlib.h>

// NOTE: Write a neural network that takes a number and doubles it

const int ITERATIONS = 2;

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

int main() {
    float node_weight = (float)rand() / RAND_MAX;
    float node_bias = 0.0f;

    for (int i = 0; i < ITERATIONS; i++) {
        float input = (float)rand() / RAND_MAX;

        float expected_output = input * 2.0f;
        float node_output = relu(input * node_weight) + node_bias;

        float error = expected_output - node_output;

        printf("Doubling number\nInput: %f\nWeight: %f\nNetwork Response: %f\nCorrect Response: %f\nError: %f\n\n", input, node_weight, node_output, expected_output, error);

        node_weight += (error / input) / relu_derivative(input);
    }

    return 0;
}
