#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

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
