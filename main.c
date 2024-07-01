#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float train[][2] = {
    {0, 0}, {1, 2}, {2, 4}, {3, 6}, {4, 8},
};

#define train_count sizeof(train) / sizeof(train[0])

float rand_float() { return (float)rand() / (float)RAND_MAX; }

float cost(float guess) {
  float result = 0.0f;
  for (size_t i = 0; i < train_count; ++i) {
    float input = train[i][0];
	float output = train[i][1];
    float result = input * guess;
    float difference = result - output;
    result += difference * difference;
  }
  result /= (float)train_count;

  return result;
}

int main() {
  srand(time(0));
  float guess = rand_float() * 10.0f;

  float eps = 1e-3;
  float rate = 1e-3;

  printf("%f\n", cost(guess));

  for (size_t i = 0; i < 1000; ++i) {
    float cost_derivative = (cost(guess + eps) - cost(guess)) / eps;
    printf("%f\n", cost(guess));
    guess -= rate * cost_derivative;
    printf("%f\n", cost(guess));
	if (cost(guess) <= 0.000001) {
		break;
	}
  }
  printf("--------------------\n");
  printf("%f\n", guess);
  return 0;
}
