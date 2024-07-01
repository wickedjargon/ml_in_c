#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float train[][2] = {
    {0, 0}, {1, 2}, {2, 4}, {3, 6}, {4, 8},
};

#define train_count sizeof(train) / sizeof(train[0])

float rand_float() { return (float)rand() / (float)RAND_MAX; }


/* computes the mean squared error (MSE) between the `predicted_output` (input * guess)
   and the `actual_outputs` (train[i][1]) */
float cost(float guess) {
    float total_cost = 0.0f;
    for (size_t i = 0; i < train_count; i++) {
        float input = train[i][0];
        float output = train[i][1];
        float predicted_output = input * guess;
        float difference = predicted_output - output;
        total_cost += difference * difference;
    }
    total_cost /= (float)train_count;

    return total_cost;
}

int main() {
  /* srand(time(0)); */
  /* float guess = rand_float() * 10.0f; */
  float guess = 2.5;
  printf("guess: %f\n", guess);

  float epsilon = 0.001;
  for (size_t i = 0; 1; i++) {
    /* computes the cost_derivative using the finite difference method */
	float cost_w_epsilon = cost(guess + epsilon);
	float cost_wo_epsilon = cost(guess);
    float cost_derivative = cost_w_epsilon - cost_wo_epsilon;
	printf("guess before: %f\n", guess);
    guess -= cost_derivative;
	printf("cost_w_epsilon: %f\n", cost_w_epsilon);
	printf("cost_wo_epsilon: %f\n", cost_wo_epsilon);
	printf("cost_derivative: %f\n", cost_derivative);
	printf("guess after: %f\n", guess);
	printf("--------------------\n");
	if (cost(guess) <= 0.000003) {
		break;
	}
	break;
  }
  printf("--------------------\n");
  printf("%f\n", guess);
  return 0;
}
