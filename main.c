#include <stdio.h>
#include <stdlib.h>

/* Training data */
float train[][2] = {
    {0, 0}, {1, 2}, {2, 4}, {3, 6}, {4, 8},
};

#define train_count (sizeof(train) / sizeof(train[0]))

/* Computes the mean squared error (MSE) between the predicted_output (input * guess) and the actual_outputs (train[i][1]) */
float cost(float guess) {
    float total_cost = 0.0f;
    for (size_t i = 0; i < train_count; i++) {
        float input = train[i][0];
        float output = train[i][1];
        float guess_output = input * guess;
        float difference = guess_output - output;
        total_cost += difference * difference;
    }
    total_cost /= (float)train_count;

    return total_cost;
}

int main() {
    /* File to save the iteration data */
    FILE *fp = fopen("spreadsheet.csv", "w");
    if (fp == NULL) {
        perror("Unable to open file");
        return 1;
    }

    /* Write the header to the CSV file */
    fprintf(fp, "Iteration,Guess,Cost\n");

    float guess = 0.000001f;
    float epsilon = 0.001;
    float learning_rate = 0.01;
    size_t max_iterations = 10000;

    for (size_t i = 0; i < max_iterations; i++) {
        float cost_w_epsilon = cost(guess + epsilon);
        float cost_wo_epsilon = cost(guess);
        float cost_derivative = (cost_w_epsilon - cost_wo_epsilon) / epsilon;

        guess -= learning_rate * cost_derivative;

        /* Write the current iteration data to the CSV file */
        fprintf(fp, "%zu,%f,%f\n", i, guess, cost(guess));

        if (cost(guess) <= 0.000003) {
            break;
        }
    }

    fclose(fp);

    printf("Final guess: %f\n", guess);
    return 0;
}
